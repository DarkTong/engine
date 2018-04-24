#version 330 core

in vec2 fragTexCoords;

out vec4 FragColor;

uniform sampler2D show_texture;

void main()
{
    float depth =  texture(show_texture, fragTexCoords).r;
    FragColor = vec4(vec3(depth), 1.0);
}