#version 330 core
out vec4 FragColor;

in vec2 uv;// pixel coodinates
uniform vec3 bg_color;
void main()
{
    float distance = length(uv); 
    if (distance > 0.5){
        FragColor.rgb = bg_color; // Outside the circle
    } else {
        FragColor.rgb = vec3(1.0); // Inside the circle
    }
    FragColor.a = 1.0; // Set alpha to 1.0
    
}
