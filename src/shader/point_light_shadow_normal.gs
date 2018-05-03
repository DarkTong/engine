#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

out TangentSpaceD
{
	vec3 fragPosition;
	vec3 fragNormal;
	vec3 fragViewPosition;
	vec3 lightPosition;
	vec3 lightDirection;
}fs_data;

in VS_2_GS
{
	vec3 position;
	vec3 normal;
	vec2 texCoords;	
	vec4 lightSpacePos;
	vec3 lightWorldPos;
	vec3 lightWorldDir;
}gs_data[];

out vec4 fragLightSpacePos;
out vec2 fragTexCoords;

uniform vec3 view_position;

mat4 tangentSpace;

void GeneralTangentSpaceMatrix();

void GeneralVertex(int index);

void main()
{
	GeneralTangentSpaceMatrix();
	// 片段着色器使用的光空间位置
	fragLightSpacePos = gs_data[0].lightSpacePos;
	// 观察位置
	fs_data.fragViewPosition = vec3(tangentSpace * vec4(view_position, 1.0f));


	GeneralVertex(0);
	GeneralVertex(1);
	GeneralVertex(2);

	EndPrimitive();

}

void GeneralTangentSpaceMatrix()
{
	float _du1 = gs_data[1].texCoords.x - gs_data[0].texCoords.x;
	float _dv1 = gs_data[1].texCoords.y - gs_data[0].texCoords.y;

	float _du2 = gs_data[2].texCoords.x - gs_data[0].texCoords.x;
	float _dv2 = gs_data[2].texCoords.y - gs_data[0].texCoords.y;

	float k = 1.0f / (_du1*_dv2 - _du2*_dv1);
	vec3 e1 = gs_data[1].position - gs_data[0].position;
	vec3 e2 = gs_data[2].position - gs_data[0].position;

	vec3 T = normalize(k * vec3(dot(vec2(_dv2, -_dv1), vec2(e1.x, e2.x))
				, dot(vec2(_dv2, -_dv1), vec2(e1.y, e2.y))
				, dot(vec2(_dv2, -_dv1), vec2(e1.z, e2.z))));
	vec3 B = normalize(k * vec3(dot(vec2(-_du2, _du1), vec2(e1.x, e2.x))
				, dot(vec2(-_du2, _du1), vec2(e1.y, e2.y))
				, dot(vec2(-_du2, _du1), vec2(e1.z, e2.z))));
	vec3 N = cross(T, B);

	tangentSpace = transpose(
		mat4(vec4(T, 0), 
			vec4(B, 0),
			vec4(N, 0), 
			vec4(vec3(0), 1))
		);
}

void GeneralVertex(int index)
{
	gl_Position = gl_in[index].gl_Position;
	// 纹理坐标
	fragTexCoords = gs_data[index].texCoords;
	// fs_data.fragPosition = vec3(tangentSpace * vec4(gs_data[index].position, 1.0f));
	fs_data.fragPosition = gs_data[index].position;
	fs_data.fragNormal = mat3(tangentSpace) * gs_data[index].normal;
	// 光源位置
	fs_data.lightPosition = vec3(tangentSpace * vec4(gs_data[index].lightWorldPos, 1.0f));
	// 光源方向
	fs_data.lightDirection = mat3(tangentSpace) * gs_data[index].lightWorldDir;

	EmitVertex();
}