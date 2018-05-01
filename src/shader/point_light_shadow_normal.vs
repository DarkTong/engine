#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;

struct PointLightTransform
{
    vec3 position;
    vec3 direction;
};

uniform PointLightTransform light_transform;

out VS_2_GS
{
	vec3 position;
	vec3 normal;
	vec2 texCoords;	
	vec4 lightSpacePos;
	vec3 lightWorldPos;
	vec3 lightWorldDir;
}gs_data;

uniform mat4 local2world;
uniform mat4 world2view;
uniform mat4 view2projection;
// ¹âµÄworld2view¾ØÕó
uniform mat4 light_space;

void main()
{
	vec3 worldPos = vec3(local2world * vec4(aPos, 1.0));
    gs_data.position = worldPos;
    gs_data.normal = mat3(local2world) * aNormal;
    gs_data.texCoords = aTexCoords;
    gs_data.lightSpacePos = light_space * vec4(worldPos, 1.0);
    gs_data.lightWorldPos = vec3(local2world * vec4(light_transform.position, 1.0));
    gs_data.lightWorldDir = mat3(local2world) * light_transform.direction;

    gl_Position = view2projection * world2view * vec4(worldPos, 1.0);
}