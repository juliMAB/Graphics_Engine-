#version 330 core
in vec3 ourColor;
uniform float alpha = 1.0f;
uniform vec3 tintColor;
out vec4 FragColor;

void main()
{
	FragColor = vec4(ourColor* tintColor, alpha);
}