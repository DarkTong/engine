#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;

uniform mat4 local2world;
uniform mat4 world2view;
uniform mat4 view2projection;

out vec3 fragPosition;
out vec3 fragNormal;
out vec2 fragTexCoords;

void main()
{
    fragPosition = vec3(local2world * vec4(aPos, 1.0));
    fragNormal = mat3(local2world) * aNormal;
    fragTexCoords = aTexCoords;

    gl_Position = view2projection * world2view * vec4(fragPosition, 1.0);
}