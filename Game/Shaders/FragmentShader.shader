#version 330 core
in vec3 ourColor;
in vec2 TexCoord;

uniform vec3 color = vec3(1.0f,1.0f,1.0f);
uniform float alpha = 1.0f;
uniform bool useTexture = false;

out vec4 FragColor;

uniform sampler2D theTexture;

void main()
{
    if(useTexture == false)
    FragColor = vec4(ourColor * color, 1.0f);
	else
        FragColor = texture(theTexture, TexCoord) * vec4(ourColor * color, 1.0f);
}