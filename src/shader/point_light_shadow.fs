#version 330 core

in vec3 fragPosition;
in vec3 fragNormal;
in vec2 fragTexCoords;
in vec4 fragLightSpacePos;

out vec4 FragColor;

struct PointLight
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

struct LightTransform
{
    vec3 position;
    vec3 direction;
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
    // 材质反射材质
    vec3 specular_color;

    // 标志位（标志是否使用texture
    bool diffuse_tex_use;
    bool specular_tex_use;
    bool normal_tex_use;

    int shininess;
};

// ÄŁĐÍ˛ÄÖĘĐĹĎ˘
uniform MeshMaterial mesh_mate;
// Ć˝ĐĐąâĐĹĎ˘
uniform PointLight light;

uniform LightTransform light_transform;
// ÉăĎń»úÎ»ÖĂ
uniform vec3 view_position;
// ŇőÓ°ĚůÍĽ
uniform sampler2D shadow_texture;

uniform int is_open_shadow;

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
    float dis = length(fragPosition - light_transform.position);
    float currentDepth = dis / light.far_plane;
    // 0.0 is shadow, 1.0 is not shadow
    // Éî¶ČĆ«ŇĆÖµŁ¬˝âľöÉî¶ČłĺÍ»
    float shadow_bias = 0.005;
    // ĹĐ¶Ďµ±Ç°Ć¬¶ÎĘÇ˛»ĘÇŇőÓ°
    float shadow = closeDepth < currentDepth - 0.005? 0.0f : 1.0;
    // ÉčÖĂÎŢĎŢÔ¶´¦˛»ĘÇŇőÓ°Đ§ąű
    shadow = projCoords.z > 1.0f ? 1.0 : shadow;

    return shadow;
}

vec3 CalPointLight()
{
    vec3 viewDir = normalize(view_position - fragPosition);
    vec3 lightDir = normalize(light_transform.position - fragPosition);
    vec3 normal = normalize(fragNormal);
    vec3 reflectDir = normalize(reflect(-lightDir, fragNormal));

    float intensity = light.intensity;
    float diff = intensity * max(dot(normal, lightDir), 0.0);
    float spec = intensity * pow(max(dot(viewDir, reflectDir), 0.0), mesh_mate.shininess); 

    vec3 color = GetDiffuse();
    vec3 diffuse = diff * light.diffuse;
    vec3 specular = spec * light.specular * GetSpecular();

    // attenuation
    float distance = length(light_transform.position - fragPosition);
    float attenuation = 1.0 / (1.0 
        + light.param_k1 * distance + light.param_k2 * (distance * distance));  

    // calcular the result color
    float shadow = CalShadow() + 1.0 * (1 - is_open_shadow);
    // ĽĆËăĆ¬¶Î×îÖŐµÄŃŐÉ«Öµ
    vec3 result_color = (intensity * light.ambient + 
        shadow * (diffuse + specular) * attenuation) * color ;

    return result_color;
}

void main()
{
    vec3 color = CalPointLight();

    FragColor = vec4(color, 1.0);
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
