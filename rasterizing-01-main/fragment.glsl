#version 330 core

in vec3 pos;
in vec2 uv;
in vec3 normal;

out vec4 FragColor;

void main()
{
   FragColor = vec4((pos.x+1)/2, (pos.y+1)/2, 0.0f, 1.0f);
}