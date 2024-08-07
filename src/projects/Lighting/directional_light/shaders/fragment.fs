#version 330 core
out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;
in vec2 TextCoord;

struct Material {
    sampler2D diffuse;
    sampler2D specular;    
    float shininess;
}; 

struct Light {
    // vec3 position;
    // position no longer required
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

};

uniform Light light;
uniform vec3 viewPos;
uniform Material material;

void main()
{
    // ambient
    vec3 ambient =  light.ambient * vec3(texture(material.diffuse, TextCoord));
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TextCoord));

    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TextCoord));
            
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
} 