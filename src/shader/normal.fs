#version 330 core

in vec2 fragTexCoords;

out vec4 FragColor;

struct MeshMaterial
{
    // ��������ͼ
    sampler2D diffuseTexture;
    // ������ͼ
    sampler2D specularTexture;
    // ����ָ��
    int shininess;
};

// ģ�Ͳ�����Ϣ
uniform MeshMaterial mesh_mate;

void main()
{
    vec3 diffuse = vec3(texture(mesh_mate.diffuseTexture, fragTexCoords));
    vec3 specular = vec3(texture(mesh_mate.specularTexture, fragTexCoords));
    vec3 color = diffuse + specular;

    FragColor = vec4(color, 1.0);
}