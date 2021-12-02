#version 330 core
in vec4 vertexColor;
out vec4 FragColor;

uniform vec3 color = vec3(1.0f, 1.0f, 1.0f);
uniform float a = 1.0f;

void main()
{
		FragColor = vec4(vertexColor * vec4(color,a));
}