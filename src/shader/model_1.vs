#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 2) in vec2 aTexCoords;

out vec2 TexCoords;

uniform mat4 local2world;
uniform mat4 world2view;
uniform mat4 view2projection;

void main(){
    TexCoords = aTexCoords;
    gl_Position = view2projection * world2view * local2world * vec4(aPos, 1.0f);
} 
