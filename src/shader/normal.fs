#version 330 core

in vec2 fragTexCoords;

out vec4 FragColor;

struct MeshMaterial
{
    // 漫反射贴图
    sampler2D diffuseTexture;
    // 镜面贴图
    sampler2D specularTexture;
    // 反光指数
    int shininess;
};

// 模型材质信息
uniform MeshMaterial mesh_mate;

void main()
{
    vec3 diffuse = vec3(texture(mesh_mate.diffuseTexture, fragTexCoords));
    vec3 specular = vec3(texture(mesh_mate.specularTexture, fragTexCoords));
    vec3 color = diffuse + specular;

    FragColor = vec4(color, 1.0);
}