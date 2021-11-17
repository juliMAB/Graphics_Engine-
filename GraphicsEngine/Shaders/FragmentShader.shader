#version 330 core
in vec4 vertexColor;
in vec2 TexCoord;
out vec4 FragColor;

uniform vec3 color = vec3(1.0f, 1.0f, 1.0f);
uniform float alpha = 1.0f;
uniform bool useTexture = false;
uniform sampler2D theTexture;

void main()
{
	if (useTexture == false)
		FragColor = vec4(vertexColor * vec4(color,alpha));
	else
		FragColor = texture(theTexture, TexCoord) * vec4(vertexColor);

}