#version 330 core
in vec3 ourColor;
in vec2 TexCoord;

uniform float alpha;
uniform bool useTexture = false;

out vec4 FragColor;

uniform sampler2D theTexture;

void main()
{
    if(useTexture == false)
		FragColor = vec4(ourColor, alpha);
	else
        FragColor = texture(theTexture, TexCoord) * vec4(ourColor, alpha);
}