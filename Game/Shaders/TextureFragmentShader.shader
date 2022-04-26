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
uniform vec3 viewPos;
uniform float ambientStrength = 1.0f;
float specularStrength = 0.5;

void main()
{
	vec4 basic = vec4(1.0f, 1.0f, 1.0f,1.0f);
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	vec3 result = vec3(1.0f, 1.0f, 1.0f);

	basic = vec4(color, alpha);

		
	if (useTexture == true)
		basic = texture(theTexture, TexCoord) * basic;
	if (affectedLight == true)
	{
	ambient = ambientStrength * lightColor;

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);

	float diff = max(dot(norm, lightDir), 0.0);
	diffuse = diff * lightColor;

	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 128);
	specular = specularStrength * spec * lightColor;
	result = (ambient+diffuse+specular)*color;
	}
	FragColor = vec4(result,1.0)*basic;

}