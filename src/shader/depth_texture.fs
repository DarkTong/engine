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
    // 计算线性空间的深度值
    float dis = length(FragPos - light_transform.position);
    // 将深度值写入深度缓存
    gl_FragDepth = dis / light.far_plane;
}