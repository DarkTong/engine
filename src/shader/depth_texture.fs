#version 330 core

in vec3 FragPos;

struct Light
{
    float near_plane;
    float far_plane;
};
struct LightTransform
{
	vec3 position;
};

uniform Light light;
uniform LightTransform light_transform;
uniform float far_plane;
uniform float near_plane;

void main()
{
    // �������Կռ�����ֵ
    float dis = length(FragPos - light_transform.position);
    // �����ֵд����Ȼ���
    gl_FragDepth = dis / light.far_plane;
}