#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;
layout (location = 2) in vec3 aOffset;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    TexCoords = aTexCoords;
    vec4 worldPos = model * vec4(aPos, 1.0) + vec4(aOffset, 0.0);
    gl_Position = projection * view * worldPos;
}