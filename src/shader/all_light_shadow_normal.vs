#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;
layout(location = 3) in vec3 aTangent;
layout(location = 4) in vec3 aBitangent;

struct PointLightTransform
{
    vec3 position;
    vec3 direction;
};

out VS_2_FS
{
    vec3 fragPosition;
    vec3 fragNormal;
    vec2 fragTexCoords;
    vec3 lightPosition;
    vec3 lightDirection;
    vec4 fragLightSpacePos;
    vec3 fragViewPosition;
}fs_data;

// space
uniform mat4 local2world;
uniform mat4 world2view;
uniform mat4 view2projection;

// light space
uniform mat4 light_space;

// light transform data
uniform PointLightTransform light_transform;

// view position (camera position)
uniform vec3 view_position;

out mat3 tangentSpace;

mat3 normalMatrix;

void CalTangentSpace();

void main()
{
    normalMatrix = transpose(inverse(mat3(local2world)));
    vec3 worldPos = vec3(local2world * vec4(aPos, 1.0));

    CalTangentSpace();
    fs_data.fragPosition = worldPos;
    fs_data.fragNormal = normalMatrix * aNormal;
    fs_data.fragTexCoords = aTexCoords;
    fs_data.fragLightSpacePos = light_space * vec4(worldPos, 1.0);
    fs_data.lightPosition = light_transform.position;
    fs_data.lightDirection = light_transform.direction;
    fs_data.fragViewPosition = view_position;

    gl_Position = view2projection * world2view * vec4(worldPos, 1.0);
}

void CalTangentSpace()
{
    vec3 T = normalize(normalMatrix * aTangent);
    vec3 B = normalize(normalMatrix * aBitangent);
    vec3 N = normalize(normalMatrix * aNormal);
    T = normalize(T - dot(T, N) * N);
    if( dot(cross(N, T), B) < 0.0f )
        T = T * -1.0f;
    

    tangentSpace = mat3(T,B,N);
}
