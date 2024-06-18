#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec4 FragPos;
// texture samplers
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

void main()
{	
	float ambientStrength =  0.1;
	vec3 ambient = ambientStrength * lightColor;

	vec3 norm = normalise(Normal);
	vec3 lightDir = normalise(lightPos - FragPos);

	float diff = max(dot(norm, lightDir). 0.0);

	vec3 diffuse = diff * lightColor;
	vec3 result = (ambient + diffuse)  * objectColor;
	FragColor = vec4(result, 1.0);
}