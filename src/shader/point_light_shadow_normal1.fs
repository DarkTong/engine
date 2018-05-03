#version 330 core

in VS_2_FS
{
    vec3 fragPosition;
    vec3 fragNormal;
    vec2 fragTexCoords;
    vec3 lightPosition;
    vec4 fragLightSpacePos;
    vec3 fragViewPosition;
}fs_data;


out vec4 FragColor;

struct PointLightD
{
    vec3 color;
    float intensity;
    float near_plane;
    float far_plane;
    
    float param_k1;
    float param_k2;
};

struct MeshMaterial
{
    // 漫反射贴图
    sampler2D diffuse_texture;
    // 高光反射贴图
    sampler2D specular_texture;
    // 法线贴图
    sampler2D normal_texture;

    // 材质漫放射颜色
    vec3 diffuse_color;
    // 材质反射颜色
    vec3 specular_color;

    // 标志位（标志是否使用texture
    bool diffuse_tex_use;
    bool specular_tex_use;
    bool normal_tex_use;

    // 反射系数
    int shininess;

    // 是否使用blinn_light模型
    bool BLINN;
};

// 环境光
uniform vec3 ambient_color;
// 材质
uniform MeshMaterial mesh_mate;
// 光源
uniform PointLightD light;
// 深度贴图
uniform sampler2D shadow_texture;

uniform bool is_open_shadow;

in mat3 tangentSpace;

vec3 GetNormal();

vec3 GetDiffuse();

vec3 GetSpecular();

float CalShadow();

float CalSpecularValue(vec3 lightDir, vec3 viewDir, vec3 normal);

vec3 CalPointLight();

void main()
{
    vec3 color = CalPointLight();

    FragColor = vec4(color, 1.0);
}

float CalShadow()
{
    // ˝řĐĐÍ¸ĘÓłý·¨Ł¬ČçąűĘÇŐý˝»żŐĽäĽĆËăw=1,
    vec3 projCoords = fs_data.fragLightSpacePos.xyz / fs_data.fragLightSpacePos.w;
    // ÖµÓňµÄ×Ş»»
    // ÓÉÓÚprojCoordsµÄ·¶Î§ĘÇ[-1,1]Ł¬¶řÎĆŔí×ř±ęµÄ·¶Î§ĘÇ[0,1],
    projCoords = projCoords * 0.5 + 0.5;
    // »ńČˇÉî¶ČĚůÍĽ¶ÔÓ¦Î»ÖĂµÄÉî¶ČÖµ
    float closeDepth = texture(shadow_texture, projCoords.xy).r;
    // ŔűÓĂÉî¶ČĽÄ´ćĆ÷Éî¶ČŁ¬żÉÄÜĘÇ·ÇĎßĐÔżŐĽäµÄ
    // float currentDepth = projCoords.z;
    // »ńČˇĎßĐÔżŐĽäµÄÉî¶ČÖµŁ¬
    float dis = length(fs_data.fragPosition - fs_data.lightPosition);
    float currentDepth = dis / light.far_plane;
    // 0.0 is shadow, 1.0 is not shadow
    // Éî¶ČĆ«ŇĆÖµŁ¬˝âľöÉî¶ČłĺÍ»
    float shadow_bias = 0.005;
    // ĹĐ¶Ďµ±Ç°Ć¬¶ÎĘÇ˛»ĘÇŇőÓ°
    float shadow = closeDepth < currentDepth - 0.005 ? 0.0f : 1.0;
    // ÉčÖĂÎŢĎŢÔ¶´¦˛»ĘÇŇőÓ°Đ§ąű
    shadow = projCoords.z > 1.0f ? 1.0 : shadow;

    return shadow;
}

float CalSpecularValue(vec3 lightDir, vec3 viewDir, vec3 normal)
{
    if( mesh_mate.BLINN )
    {
        vec3 halfwardir = normalize(lightDir + viewDir);
        return pow(
            dot(halfwardir, normal), mesh_mate.shininess
        );
    }
    else
    {
        vec3 reflectDir = normalize(reflect(-lightDir, normal));
        return pow(
            max(dot(reflectDir, viewDir), 0.0), mesh_mate.shininess
        );
    }
}

vec3 GetNormal()
{
    if(mesh_mate.normal_tex_use)
        return normalize(vec3(texture(mesh_mate.normal_texture, fs_data.fragTexCoords)) * 2.0 - 1.0);    
    return normalize(fs_data.fragNormal * tangentSpace);
}

vec3 GetDiffuseColor()
{
    if(mesh_mate.diffuse_tex_use)
        return texture(mesh_mate.diffuse_texture, fs_data.fragTexCoords).rgb;
    return mesh_mate.diffuse_color;
}

vec3 GetSpecularColor()
{
    if(mesh_mate.specular_tex_use)
        return texture(mesh_mate.specular_texture, fs_data.fragTexCoords).rgb;
    return mesh_mate.specular_color;
}

vec3 CalPointLight()
{
    vec3 viewDir = normalize(fs_data.fragViewPosition - fs_data.fragPosition);
    vec3 lightDir = normalize(fs_data.lightPosition - fs_data.fragPosition);
    vec3 normal = GetNormal();

    viewDir = normalize(tangentSpace * viewDir);
    lightDir = normalize(tangentSpace * lightDir);

    float intensity = light.intensity;
    float diff = intensity * max(dot(normal, lightDir), 0.0);
    float spec = intensity * CalSpecularValue(lightDir, viewDir, normal);

    vec3 ambientColor = ambient_color;

    // diffuse
    vec3 diffuseColor = GetDiffuseColor();
    vec3 diffuse = diff * diffuseColor;

    // specular
    vec3 specularColor = GetSpecularColor();
    vec3 specular = spec * specularColor;

    // attenuation
    float distance = length(fs_data.lightPosition - fs_data.fragPosition);
    float attenuation = 1.0 / (1.0 
        + light.param_k1 * distance + light.param_k2 * (distance * distance));  

    // shadow
    float shadow = 1.0f;
    if(is_open_shadow)
        shadow = CalShadow();

    // calcular the result fragment color
    vec3 result_color = ambientColor * diffuseColor +
        shadow * (diffuse + specular) * attenuation * light.color;

    // return normal * 0.5 + 0.5;
    return result_color;
}
