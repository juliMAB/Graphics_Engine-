#version 330 core
in vec4 vertexColor;
in vec2 TexCoord;
out vec4 FragColor;

uniform vec3 color = vec3(1.0f, 1.0f, 1.0f);
uniform float alpha = 1.0f;
uniform bool useTexture = false;
uniform sampler2D theTexture;
uniform vec3 lightColor;
void main()
{
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * lightColor;

	vec4 result;

	if (useTexture == false)
		result = vec4(vertexColor * vec4(color, alpha));
	else
		result = texture(theTexture, TexCoord) * vec4(vertexColor * vec4(color, alpha));

	vec3 ambientColor = ambient * color;
	FragColor = result * vec4(ambientColor, 1.0);
}