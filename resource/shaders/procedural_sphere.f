#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

void main()
{
	FragColor = vec4(vec3(1.0f), 1.0f);
}
