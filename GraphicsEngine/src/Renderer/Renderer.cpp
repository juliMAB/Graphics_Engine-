#include "Renderer.h"
#include <iostream>
#include "../../Lib/GLM/gtc/type_ptr.hpp"

Renderer::Renderer() {
	_window = nullptr;
	programShader = NULL;
}
Renderer::~Renderer()
{
}
void Renderer::Awake(Window* window) {
	_window = window;
}
void Renderer::Start() {
	ShadersStart();
}
void Renderer::Update() {
	SetClearWindow(1, 1, 1, 1);
	//DrawTriangle();
}
void Renderer::Exit() {

}
void Renderer::BeginDrawing() {
	
}
void Renderer::SetClearWindow(float r, float g, float b, float a) {
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
}
void Renderer::ClearWindow() {
	glClear(GL_COLOR_BUFFER_BIT);
}
std::string Renderer::ReadVertexShader() {
	std::string vertexCode;
	std::ifstream vShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try	{
		vShaderFile.open(vertexPath);
		std::stringstream vShaderStream, fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		vShaderFile.close();
		vertexCode = vShaderStream.str();
	}
	catch (std::ifstream::failure& e) {
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	return vertexCode;
}
std::string Renderer::ReadFragmentShader() {
	std::string fragmentCode;
	std::ifstream fShaderFile;

	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try	{
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		fShaderStream << fShaderFile.rdbuf();
		fShaderFile.close();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure& e) {
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	return fragmentCode;	
}
void Renderer::ShadersStart() {
	std::string vShaderSource = ReadVertexShader();
	std::string fShaderSource = ReadFragmentShader();
	
	const char* vertexShaderSource = vShaderSource.c_str();
	const char* fragmentShaderSource = fShaderSource.c_str();
	
	unsigned int vertexShader = NULL;
	unsigned int fragmentShader = NULL;

	programShader = glCreateProgram();
	if (!programShader) {
		std::cout << "Error creating the shader program!" << std::endl;
		return;
	}
	SetVertexShader(vertexShader, vertexShaderSource);
	SetFragmentShader(fragmentShader, fragmentShaderSource);
	LinkShaders(vertexShader, fragmentShader);
	//SetTriangle();
}
void Renderer::ShadersUpdate() {
	
}
void Renderer::SetVertexShader(unsigned int &vertexShader, const char* vertexShaderSource) {
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}
void Renderer::SetFragmentShader(unsigned int &fragmentShader, const char* fragmentShaderSource) {
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	int success;
	char infoLog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}
void Renderer::LinkShaders(unsigned int vertexShader, unsigned int fragmentShader) {
	programShader = glCreateProgram();
	glAttachShader(programShader, vertexShader);
	glAttachShader(programShader, fragmentShader);
	glLinkProgram(programShader);

	int success;
	char infoLog[512];
	glGetProgramiv(programShader, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(programShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;	// Acá tira error. 
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}
//void Renderer::DrawTriangle() {
//	glUseProgram(programShader);
//	glBindVertexArray(VAO);
//	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);	
//}
//void Renderer::SetTriangle() {
//	float vertices[] = {
//		 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // top right
//		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // bottom right
//		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom left
//		-0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f  // top left 
//	};
//	unsigned int indices[] = {  // note that we start from 0!
//		0, 1, 3,  // first Triangle
//		1, 2, 3   // second Triangle
//	};
//	
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
//	glGenBuffers(1, &EBO);
//
//	glBindVertexArray(VAO);
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
//	glEnableVertexAttribArray(1);
//
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindVertexArray(0);
//}
void Renderer::SetBuffers(int tam, float* verts, uint& vbo, uint& vao) {
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, tam, verts, GL_STATIC_DRAW);

}
void Renderer::SetIndex(int tam, uint* indexs, uint& ibo) {
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, tam, indexs, GL_STATIC_DRAW);
}
void Renderer::Setattributes(uint location, int size, int stride, int offset) {
	glVertexAttribPointer(location, size, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(offset * sizeof(float)));
	glEnableVertexAttribArray(location);
}
void Renderer::Draw(TypeShape shape, int verts, uint vao, uint vbo, uint ibo, float* vertexs, float tamVertexs, TypeShader t) {
	
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ARRAY_BUFFER, tamVertexs, vertexs, GL_STATIC_DRAW);

	glUseProgram(programShader);

	glEnable(GL_DEPTH_TEST);

	if (shape == TypeShape::Triangle)
		glDrawArrays(GL_TRIANGLES, 0, 3);
	else
		glDrawElements(GL_TRIANGLES, verts, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glUseProgram(0);
}
void Renderer::UpdateMVP(glm::mat4 model, uint transformLoc) {
	glUseProgram(GetShader());
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUseProgram(0);
}