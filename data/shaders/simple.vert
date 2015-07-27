#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec4 color;

uniform mat4 projection;

out DATA{
  vec4 color;
  vec2 uv;
} vs_out;

void main()
{
    gl_Position  = projection*vec4(position, 1.0);
    vs_out.color = color;
    vs_out.uv    = uv;
}
