#version 330 core

in TangentSpaceD
{
    vec3 fragPosition;
    vec3 fragNormal;
    vec3 fragViewPosition;
    vec3 lightPosition;
    vec3 lightDirection;
}fs_data;

in vec4 fragLightSpacePos;
in vec2 fragTexCoords;

out vec4 FragColor;

struct PointLightD
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float intensity;
    float near_plane;
    float far_plane;
    
    float param_k1;
    float param_k2;
};

struct MeshMaterial
{
    // Âţ·´ÉäĚůÍĽ
    sampler2D diffuse_texture;
    // ľµĂćĚůÍĽ
    sampler2D specular_texture;
    // 法线贴图
    sampler2D normal_texture;

    // 材质漫放射颜色
    vec3 diffuse_color;
    // 材质反射材质
    vec3 specular_color;

    // 标志位（标志是否使用texture
    bool diffuse_tex_use;
    bool specular_tex_use;
    bool normal_tex_use;

    // ·´ąâÖ¸Ęý
    int shininess;
};


// ÄŁĐÍ˛ÄÖĘĐĹĎ˘
uniform MeshMaterial mesh_mate;
// Ć˝ĐĐąâĐĹĎ˘
uniform PointLightD light;
// ŇőÓ°ĚůÍĽ
uniform sampler2D shadow_texture;

uniform bool is_open_shadow;

vec3 GetNormal();
vec3 GetDiffuse();
vec3 GetSpecular();

float CalShadow()
{
    // ˝řĐĐÍ¸ĘÓłý·¨Ł¬ČçąűĘÇŐý˝»żŐĽäĽĆËăw=1,
    vec3 projCoords = fragLightSpacePos.xyz / fragLightSpacePos.w;
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


vec3 CalPointLight()
{
    vec3 viewDir = normalize(fs_data.fragViewPosition - fs_data.fragPosition);
    vec3 lightDir = normalize(fs_data.lightPosition - fs_data.fragPosition);
    vec3 normal = GetNormal().rgb;
    normal = normal * 2.0 - 1.0;
    vec3 reflectDir = normalize(reflect(-lightDir, normal));

    float intensity = light.intensity;
    float diff = intensity * max(dot(viewDir, lightDir), 0.0);
    float spec = intensity * pow(max(dot(viewDir, reflectDir), 0.0), mesh_mate.shininess); 

    vec3 color = GetDiffuse().rgb;
    vec3 diffuse = diff * light.diffuse;
    vec3 specular = spec * light.specular * GetSpecular().rgb;

    // attenuation
    float distance = length(fs_data.lightPosition - fs_data.fragPosition);
    float attenuation = 1.0 / (1.0 
        + light.param_k1 * distance + light.param_k2 * (distance * distance));  

    // calcular the result color
    float shadow = 1.0f;
    if(is_open_shadow)
        shadow = CalShadow();

    // calcular the result fragment color
    vec3 result_color = (intensity * light.ambient + 
        shadow * (diffuse + specular) * attenuation) * color ;

    return result_color;
}

void main()
{
    vec3 color = CalPointLight();

    FragColor = vec4(color, 1.0);
}

vec3 GetNormal()
{
    if(mesh_mate.normal_tex_use)
        return texture(mesh_mate.normal_texture, fragTexCoords).rgb;    
    return fs_data.fragNormal;
}

vec3 GetDiffuse()
{
    if(mesh_mate.diffuse_tex_use)
        return texture(mesh_mate.diffuse_texture, fragTexCoords).rgb;
    return mesh_mate.diffuse_color;
}

vec3 GetSpecular()
{
    if(mesh_mate.specular_tex_use)
        return texture(mesh_mate.specular_texture, fragTexCoords).rgb;
    return mesh_mate.specular_color;
}
