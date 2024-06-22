#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 projection;
// uniform mat4 view;
uniform mat4 model;
out vec2 uv;

void main()
{
	gl_Position = projection * model * vec4(aPos, 1.0);
	uv = aPos.xy;
}