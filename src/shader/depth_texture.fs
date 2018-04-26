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
    // 计算线性空间的深度值
    float dis = length(FragPos - light.position);
    // 将深度值写入深度缓存
    gl_FragDepth = dis / light.far_plane;
}