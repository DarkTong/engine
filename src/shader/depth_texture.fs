#version 330 core

in vec3 FragPos;

struct Light
{
	int type;
    float near_plane;
    float far_plane;
};
struct LightTransform
{
	vec3 direction;
	vec3 position;
};

uniform Light light;
uniform LightTransform light_transform;
uniform float far_plane;
uniform float near_plane;

void main()
{
    
    float dis;
    vec3 lightToPos = FragPos - light_transform.position;
    if(light.type == 0)
    {
    	dis = dot(lightToPos, light_transform.direction);
    }
    else
    {
    	dis = length(lightToPos);
    }
    gl_FragDepth = dis / light.far_plane;	
    
}