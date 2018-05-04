#version 330 core

in VS_2_FS
{
    vec3 fragPosition;
    vec3 fragNormal;
    vec2 fragTexCoords;
    vec3 lightPosition;
    vec3 lightDirection;
    vec4 fragLightSpacePos;
    vec3 fragViewPosition;
}fs_data;


out vec4 FragColor;

struct LightData
{
    // 0 : parallel light
    // 1 : point light
    // 2 : spot light
    int type;

    vec3 color;
    float intensity;
    float near_plane;
    float far_plane;
    
    float param_k1;
    float param_k2;

    float inner_angle;
    float outter_angle;
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
uniform LightData light;
// 深度贴图
uniform sampler2D shadow_texture;

uniform bool is_open_shadow;

in mat3 tangentSpace;

// use parament

vec3 lightDir;
vec3 viewDir;
vec3 normal;
float intensity;
float attenuation;

vec3 GetNormal();

vec3 GetDiffuse();

vec3 GetSpecular();

float CalShadow();

float CalSpecularValue();

vec3 CalculateLight();

void CalParallelLight();

void CalPointLight();

void CalSpotLight();

void main()
{
    vec3 color = CalculateLight();

    FragColor = vec4(color, 1.0);
}

float CalShadow()
{
    // ˝řĐĐÍ¸ĘÓłý·¨Ł¬ČçąűĘÇŐý˝»żŐĽäĽĆËăw=1,
    vec3 projCoords = fs_data.fragLightSpacePos.xyz / fs_data.fragLightSpacePos.w;
    // ÖµÓňµÄ×Ş»»
    // ÓÉÓÚprojCoordsµÄ·¶Î§ĘÇ[-1,1]Ł¬¶řÎĆŔí×ř±ęµÄ·¶Î§ĘÇ[0,1],
    projCoords = projCoords * 0.5 + 0.5;
    
    float closeDepth, currentDepth, dis;
    vec3 lightToPos = fs_data.fragPosition - fs_data.lightPosition;
    closeDepth = texture(shadow_texture, projCoords.xy).r;
    if (light.type == 0)
    {
        dis = dot(lightToPos, fs_data.lightDirection);
    }
    else
    {
        dis = length(lightToPos);
    }
    currentDepth = dis / light.far_plane;
    // 0.0 is shadow, 1.0 is not shadow
    // Éî¶ČĆ«ŇĆÖµŁ¬˝âľöÉî¶ČłĺÍ»
    float shadow_bias = 0.005;
    // ĹĐ¶Ďµ±Ç°Ć¬¶ÎĘÇ˛»ĘÇŇőÓ°
    float shadow = closeDepth < currentDepth - 0.005 ? 0.0f : 1.0;
    // ÉčÖĂÎŢĎŢÔ¶´¦˛»ĘÇŇőÓ°Đ§ąű
    shadow = projCoords.z > 1.0f ? 1.0 : shadow;

    // 深度贴图测试
    // if(projCoords.z > 1.0f)
    //     return 0.0f;
    // else
    //     return closeDepth;

    return shadow;
}

float CalSpecularValue()
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
        return normalize(tangentSpace * (vec3(texture(mesh_mate.normal_texture, fs_data.fragTexCoords)) * 2.0 - 1.0));    
    return normalize(fs_data.fragNormal);
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

vec3 CalculateLight()
{
    viewDir = normalize(fs_data.fragViewPosition - fs_data.fragPosition);
    lightDir = normalize(fs_data.lightPosition - fs_data.fragPosition);
    normal = GetNormal();
    intensity = light.intensity;
    attenuation = 1.0f;

    if(light.type == 0)
        CalParallelLight();
    else if(light.type == 1)
        CalPointLight();
    else if(light.type == 2)
        CalSpotLight();

    float diff = max(dot(normal, lightDir), 0.0);
    float spec = CalSpecularValue();

    // ambient
    vec3 ambientColor = ambient_color;
    // diffuse
    vec3 diffuseColor = GetDiffuseColor();
    vec3 diffuse = diff * diffuseColor;
    // specular
    vec3 specularColor = GetSpecularColor();
    vec3 specular = spec * specularColor;

    // shadow
    float shadow = 1.0f;
    if(is_open_shadow)
        shadow = CalShadow();

    vec3 result_color = ambientColor * diffuseColor +
        shadow * (diffuse + specular) * intensity * attenuation * light.color;

    // return normal * 0.5 + 0.5;
    return result_color;
}

void CalParallelLight()
{
    // calculate intensity
    intensity = light.intensity;

    // calculate attenuation
    attenuation = 1.0f;
}

void CalPointLight()
{
    // calculate intensity
    intensity = light.intensity;

    // calculate attenuation
    float distance = length(fs_data.lightPosition - fs_data.fragPosition);
    float attenuation = 1.0 / (1.0 
        + light.param_k1 * distance + light.param_k2 * (distance * distance));  
}

void CalSpotLight()
{
    // calculate intensity
    float theta = dot(lightDir, normalize(-fs_data.lightDirection));
    float ratio = (theta - light.outter_angle) / (light.inner_angle - light.outter_angle);
    ratio = ratio < 1.0f ? ratio : 1.0f;
    ratio = ratio > 0.0f ? ratio : 0.0f;

    intensity = ratio * light.intensity;

    // calculate attenuation
    float distance = length(fs_data.lightPosition - fs_data.fragPosition);
    float attenuation = 1.0 / (1.0 
        + light.param_k1 * distance + light.param_k2 * (distance * distance));  
}
