#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;

void main()
{
    FragColor = vec4(vec3(0.937,0.965,0.878), 1.0f);
}