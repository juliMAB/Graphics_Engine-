#version 330 core
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

uniform vec3 color = vec3(1.0f, 1.0f, 1.0f);
uniform float alpha = 1.0f;
uniform bool useTexture = false;
uniform bool affectedLight = false;
uniform bool affectedMaterial = false;
uniform bool affectedLightingMaps = false;
uniform sampler2D theTexture;
uniform vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
uniform vec3 lightPos = vec3(1.0f, 1.0f, 1.0f);
uniform vec3 viewPos = vec3(1.0f, 1.0f, 1.0f);
uniform float ambientStrength = 1.0f;
float specularStrength = 0.5;

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct Material2 {
	sampler2D diffuse;
	sampler2D specular;
	float     shininess;
};
uniform Material2 material2;

uniform Material material;// = Material(vec3(1.0f, 1.0f, 1.0f), vec3(1.0f, 1.0f, 1.0f), vec3(1.0f, 1.0f, 1.0f), 1.0f);

struct Light {
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform Light light;// = Light(vec3(1.0f, 1.0f, 1.0f), vec3(1.0f, 1.0f, 1.0f), vec3(1.0f, 1.0f, 1.0f), vec3(1.0f, 1.0f, 1.0f));

void main()
{
	vec4 basic = vec4(1.0f, 1.0f, 1.0f,1.0f);
	vec3 ambient = vec3(1.0f, 1.0f, 1.0f);
	vec3 diffuse = vec3(1.0f, 1.0f, 1.0f);
	vec3 specular = vec3(1.0f, 1.0f, 1.0f);
	vec3 result = vec3(1.0f, 1.0f, 1.0f);

	basic = vec4(color, alpha);

		
	if (useTexture == true)
		basic = texture(theTexture, TexCoord) * basic;
	if (affectedLight == true)
	{
		if (affectedMaterial == true)
		{
			if (affectedLightingMaps==true)
			{
				//ambient
				ambient = light.ambient * vec3(texture(material2.diffuse, TexCoord));

				//diffuse
				vec3 norm = normalize(Normal);
				vec3 lightDir = normalize(lightPos - FragPos);
				float diff = max(dot(norm, lightDir), 0.0);
				diffuse = light.diffuse * diff * vec3(texture(material2.diffuse, TexCoord));


				//specular
				vec3 viewDir = normalize(viewPos - FragPos);
				vec3 reflectDir = reflect(-lightDir, norm);
				float spec = pow(max(dot(viewDir, reflectDir), 0.0), material2.shininess);
				specular = light.specular * spec * vec3(texture(material2.specular, TexCoord));
				FragColor = vec4(ambient + diffuse + specular,1.0f);
				return;
			}
			else
			{
			//ambient
			ambient = lightColor * light.ambient * material.ambient;
			//diffuse
			vec3 norm = normalize(Normal);
			vec3 lightDir = normalize(lightPos - FragPos);
			float diff = max(dot(norm, lightDir), 0.0);
			diffuse = lightColor * diff * light.diffuse;
			//specular
			vec3 viewDir = normalize(viewPos - FragPos);
			vec3 reflectDir = reflect(-lightDir, norm);
			float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
			specular = lightColor*(spec * material.specular) * light.specular;
			}
		}
		else
		{
			//ambient
			ambient = lightColor * ambientStrength;
			//diffuse
			vec3 norm = normalize(Normal);
			vec3 lightDir = normalize(lightPos - FragPos);
			float diff = max(dot(norm, lightDir), 0.0);
			diffuse = lightColor * diff;
			//specular
			vec3 viewDir = normalize(viewPos - FragPos);
			vec3 reflectDir = reflect(-lightDir, norm);
			float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
			specular = specularStrength * spec * lightColor;

		}
		//result
		result = (ambient + diffuse + specular) * color;
		log(result);
	}
	FragColor = vec4(result,1.0)*basic;

}