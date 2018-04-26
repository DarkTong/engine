#version 330 core

in vec3 FragPos;

struct Light
{
    vec3 position;
    float near_plane;
    float far_plane;
};

uniform Light light;
uniform float far_plane;
uniform float near_plane;

void main()
{
    // �������Կռ�����ֵ
    float dis = length(FragPos - light.position);
    // �����ֵд����Ȼ���
    gl_FragDepth = dis / light.far_plane;
}