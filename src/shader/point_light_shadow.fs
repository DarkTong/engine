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

    vec3 position;
    vec3 direction;
    
    float param_k1;
    float param_k2;
};

struct MeshMaterial
{
    // 漫反射贴图
    sampler2D diffuse_texture;
    // 镜面贴图
    sampler2D specular_texture;
    // 反光指数
    int shininess;
};

// 模型材质信息
uniform MeshMaterial mesh_mate;
// 平行光信息
uniform PointLight light;
// 摄像机位置
uniform vec3 view_position;
// 阴影贴图
uniform sampler2D shadow_texture;

float CalShadow()
{
    vec3 projCoords = fragLightSpacePos.xyz / fragLightSpacePos.w;
    projCoords = projCoords * 0.5 + 0.5;
    float closeDepth = texture(shadow_texture, projCoords.xy).r;
    float currentDepth = projCoords.z;
    // 0.0 is shadow, 1.0 is not shadow
    float shadow = closeDepth < currentDepth? 0.0f : 1.0;
    shadow = projCoords.z > 1.0f ? 1.0 : shadow;
    return shadow;
}

vec3 CalPointLight()
{
    vec3 viewDir = normalize(view_position - fragPosition);
    vec3 lightDir = normalize(light.position - fragPosition);
    vec3 normal = normalize(fragNormal);
    vec3 reflectDir = normalize(reflect(-lightDir, fragNormal));

    float intensity = light.intensity;
    float diff = intensity * max(dot(viewDir, lightDir), 0.0);
    float spec = intensity * pow(max(dot(viewDir, reflectDir), 0.0), mesh_mate.shininess); 

    vec3 color = vec3(texture(mesh_mate.diffuse_texture, fragTexCoords));
    vec3 diffuse = diff * light.diffuse;
    vec3 specular = spec * light.specular 
        * vec3(texture(mesh_mate.specular_texture, fragTexCoords));

    // attenuation
    float distance = length(light.position - fragPosition);
    float attenuation = 1.0 / (1.0 
        + light.param_k1 * distance + light.param_k2 * (distance * distance));  

    // calcular the result color
    float shadow = CalShadow();
    vec3 result_color = (intensity * light.ambient + 
        shadow * (diffuse + specular) * attenuation) * color ;

    return result_color;
}

void main()
{
    vec3 color = CalPointLight();

    FragColor = vec4(color, 1.0);
}