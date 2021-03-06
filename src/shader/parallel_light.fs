#version 330 core

in vec3 fragPosition;
in vec3 fragNormal;
in vec2 fragTexCoords;

out vec4 FragColor;

struct ParallelLight
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float intensity;

    vec3 position;
    vec3 direction;
    
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
uniform ParallelLight light;
// 摄像机位置
uniform vec3 view_position;

vec3 CalParallelLight()
{
    vec3 viewDir = normalize(view_position - fragPosition);
    vec3 lightDir = normalize(-light.direction);
    vec3 normal = normalize(fragNormal);
    vec3 reflectDir = normalize(reflect(-lightDir, fragNormal));

    float intensity = light.intensity;
    float diff = intensity * max(dot(viewDir, lightDir), 0.0);
    float spec = intensity * pow(max(dot(viewDir, reflectDir), 0.0), mesh_mate.shininess);

    vec3 diffuse = (diff * light.diffuse + intensity * light.ambient) 
        * vec3(texture(mesh_mate.diffuse_texture, fragTexCoords));
    vec3 specular = spec * light.specular 
        * vec3(texture(mesh_mate.specular_texture, fragTexCoords));

    return diffuse + specular;
}

void main()
{
    vec3 color = CalParallelLight();

    FragColor = vec4(color, 1.0);
}