#version 330 core
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

uniform vec3 color = vec3(1.0f, 1.0f, 1.0f);
uniform float alpha = 1.0f;
uniform bool useTexture = false;
uniform bool affectedLight = false;
uniform sampler2D theTexture;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform float ambientStrength = 1.0f;

void main()
{
	vec4 result;
	vec4 result2 = vec4(1.0f,1.0f,1.0f,1.0f);

	if (useTexture == false)
		result = vec4(color, alpha);
	else
		result = texture(theTexture, TexCoord) * vec4(color, alpha);

	if (affectedLight == true)
	{
	vec3 ambient = ambientStrength * lightColor;
	result2 = vec4(ambient, 1.0);
	}

	FragColor =result*result2;
}