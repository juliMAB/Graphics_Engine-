#ifndef VERTEXSHADER_H
#define VERTEXSHADER_H

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>


	// Vertex Shader
	static const char* vShader = "					\n\
#version 330										\n\
layout(location = 0) in vec3 pos;					\n\
layout(location = 1) in vec3 colorrrr;				\n\
layout(location = 2) in vec2 tex;					\n\
uniform mat4 model;									\n\
out vec4 vColor;									\n\
out vec2 TexCoord;									\n\
void main(){										\n\
	gl_Position =  model * vec4(pos, 1.0f);			\n\
	vColor = vec4(colorrrr, 1.0f);					\n\
	TexCoord = tex;									\n\
}";


#endif