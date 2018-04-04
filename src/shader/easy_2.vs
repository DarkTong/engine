#version 330 core

layout(location = 0) in vec3 aPos;

uniform mat4 local2world;

void main(){
    gl_Position = local2world * vec4(aPos.x, 1.0f);
} 
