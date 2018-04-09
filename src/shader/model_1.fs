#version 330 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;
// uniform sampler2D texture_diffuse2;
// uniform sampler2D texture_diffuse3;
uniform sampler2D texture_specular1;
// uniform sampler2D texture_specular2;
// uniform sampler2D texture_specular3;

void main(){
    vec3 ambient  = vec3(0.1,0.1,0.1);
    vec3 diffuse  = vec3(0.3,0.3,0.5) * vec3(texture(texture_diffuse1, TexCoords)) * 0.6f;      
    vec3 specular = vec3(0.3,0.3,0.3) * vec3(texture(texture_specular1, TexCoords)) * 0.3f;
    FragColor = vec4(ambient + diffuse + specular, 1.0f);
    // FragColor = vec4(TexCoords, 0.2f, 1.0f);
}
