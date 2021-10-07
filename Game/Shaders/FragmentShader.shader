#version 330 core
in vec3 ourColor;

uniform vec3 color = vec3(1.0f,1.0f,1.0f);
uniform float alpha = 1.0f;

out vec4 FragColor;

void main()
{
    FragColor = vec4(ourColor * color, alpha);
}