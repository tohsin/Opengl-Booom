#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 FragPos; // we need the position of the vetexes in the fragmenrts
out vec3 Normal;

void main()
{
	vec4 projection_view_model = projection * view * model;
	gl_Position = projection_view_model *  vec4(aPos, 1.0);
	Normal = aNormal;
	FragPos = vec3(mode * vec4(aPos, 1.0));
}