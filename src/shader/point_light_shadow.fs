#version 330 core

in vec3 fragPosition;
in vec3 fragNormal;
in vec2 fragTexCoords;
in vec4 fragLightSpacePos;

out vec4 FragColor;

struct PointLight
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float intensity;
    float near_plane;
    float far_plane;

    vec3 position;
    vec3 direction;
    
    float param_k1;
    float param_k2;
};

struct MeshMaterial
{
    // ��������ͼ
    sampler2D diffuse_texture;
    // ������ͼ
    sampler2D specular_texture;
    // ����ָ��
    int shininess;
};

// ģ�Ͳ�����Ϣ
uniform MeshMaterial mesh_mate;
// ƽ�й���Ϣ
uniform PointLight light;
// �����λ��
uniform vec3 view_position;
// ��Ӱ��ͼ
uniform sampler2D shadow_texture;

float CalShadow()
{
    // ����͸�ӳ���������������ռ����w=1,
    vec3 projCoords = fragLightSpacePos.xyz / fragLightSpacePos.w;
    // ֵ���ת��
    // ����projCoords�ķ�Χ��[-1,1]������������ķ�Χ��[0,1],
    projCoords = projCoords * 0.5 + 0.5;
    // ��ȡ�����ͼ��Ӧλ�õ����ֵ
    float closeDepth = texture(shadow_texture, projCoords.xy).r;
    // ������ȼĴ�����ȣ������Ƿ����Կռ��
    // float currentDepth = projCoords.z;
    // ��ȡ���Կռ�����ֵ��
    float dis = length(fragPosition - light.position);
    float currentDepth = dis / light.far_plane;
    // 0.0 is shadow, 1.0 is not shadow
    // ���ƫ��ֵ�������ȳ�ͻ
    float shadow_bias = 0.005;
    // �жϵ�ǰƬ���ǲ�����Ӱ
    float shadow = closeDepth < currentDepth - 0.005? 0.0f : 1.0;
    // ��������Զ��������ӰЧ��
    shadow = projCoords.z > 1.0f ? 1.0 : shadow;

    return shadow;
}

vec3 CalPointLight()
{
    vec3 viewDir = normalize(view_position - fragPosition);
    vec3 lightDir = normalize(light.position - fragPosition);
    vec3 normal = normalize(fragNormal);
    vec3 reflectDir = normalize(reflect(-lightDir, fragNormal));

    float intensity = light.intensity;
    float diff = intensity * max(dot(viewDir, lightDir), 0.0);
    float spec = intensity * pow(max(dot(viewDir, reflectDir), 0.0), mesh_mate.shininess); 

    vec3 color = vec3(texture(mesh_mate.diffuse_texture, fragTexCoords));
    vec3 diffuse = diff * light.diffuse;
    vec3 specular = spec * light.specular 
        * vec3(texture(mesh_mate.specular_texture, fragTexCoords));

    // attenuation
    float distance = length(light.position - fragPosition);
    float attenuation = 1.0 / (1.0 
        + light.param_k1 * distance + light.param_k2 * (distance * distance));  

    // calcular the result color
    float shadow = CalShadow();
    // ����Ƭ�����յ���ɫֵ
    vec3 result_color = (intensity * light.ambient + 
        shadow * (diffuse + specular) * attenuation) * color ;

    return result_color;
}

void main()
{
    vec3 color = CalPointLight();

    FragColor = vec4(color, 1.0);
}