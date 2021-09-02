#ifndef FRAGMENTSHADER_H
#define FRAGMNETSHADER_H



	//Fragment Shader
	static const char* fShader = "					\n\
#version 330										\n\
in vec4 vColor;										\n\
out vec4 colour;									\n\
in vec2 TexCoord;									\n\
uniform sampler2D theTexture;						\n\
uniform bool useTexture;							\n\
void main(){										\n\
	if(useTexture == false)							\n\
		colour = vColor;							\n\
	else											\n\
		colour = texture(theTexture, TexCoord);		\n\
}";



#endif