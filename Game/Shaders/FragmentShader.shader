#version 330 core
in vec4 vertexColor;

out vec4 FragColor;

uniform vec3 color = vec3(1.0f);
uniform float alpha = 1.0f;
uniform bool useTexture = false;
uniform sampler2D theTexture;

void main()
{

	FragColor = vertexColor;
	

}