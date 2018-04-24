#version 330 core

in vec3 FragPos;

struct Light
{
    vec3 position;
};

uniform Light light;
uniform float far_plane;
uniform float near_plane;

void main()
{
    float dis = length(FragPos - light.position);
    gl_FragDepth = dis / far_plane;
}