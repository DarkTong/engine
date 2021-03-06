#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;

out vec3 FragPos;

uniform mat4 local2world;
uniform mat4 light_space;

void main()
{
    vec4 _fragPos = local2world * vec4(aPos, 1.0);
    FragPos = _fragPos.xyz;
    gl_Position = light_space * _fragPos;
    
}