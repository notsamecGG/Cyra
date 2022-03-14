#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;
out vec3 pos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    vec4 resultPosition = projection * view * model * vec4(aPos, 1.0f);
    pos = aPos.xyz;
    ourColor = aPos + 0.5f;
    gl_Position = resultPosition;
}