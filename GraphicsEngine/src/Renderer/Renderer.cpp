#include "Renderer.h"
#include <iostream>
#include "../../Lib/GLM/gtc/type_ptr.hpp"

static glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1366.0f / 768.0f, 0.1f, 1000.0f);
static glm::mat4 view = glm::mat4(1.0f);
//-----C y D---------------------------
Renderer::Renderer(Window* window) {
	_window = window;
	programShader = NULL;
	Start();
}
Renderer::~Renderer()
{
}
//-------------------------------------

void Renderer::Start() {
	std::cout << "Start Renderer" << std::endl;
	ShadersStart();
	view = glm::lookAt(glm::vec3(0, 0, -5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(90.0f), (float)_window->GetWidth() / (float)_window->GetHeight(), 0.1f, 100.0f);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	std::cout << "End Start Renderer" << std::endl << std::endl;
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
void Renderer::CreateNewBuffers(uint& VAO, uint& VBO, uint& EBO)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
}
void Renderer::SetBuffers(int tam, float* verts, uint& vbo, uint& vao) {
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, tam, verts, GL_STATIC_DRAW);

}
void Renderer::BindBuffer(uint vao, uint vbo, uint ebo, float* vertices, uint sizeOfVertices, uint* indices, uint sizeOfIndices)
{
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeOfVertices, vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeOfIndices, indices, GL_STATIC_DRAW);
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
void Renderer::CreateExtraBuffer(unsigned int& buffer, int size)
{
	glGenBuffers(size, &buffer);
}
void Renderer::Draw(uint vertices, uint _vao)
{
	glBindVertexArray(_vao);
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawElements(GL_TRIANGLES, vertices, GL_UNSIGNED_INT, 0);
}

void Renderer::UpdateMVP(glm::mat4 model, uint _uniformPos, uint uniformView, uint uniformProjection, uint uniformColor,uint uniformAlpha ,glm::vec4 color) {
	glUseProgram(GetShader());
	glUniformMatrix4fv(_uniformPos, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));
	glm::vec3 newColor=glm::vec3(color.r,color.g,color.b);
	glUniform3fv(uniformColor, 1, glm::value_ptr(newColor));
	glUniform1fv(uniformAlpha, 1, &color.a);
}
void Renderer::DeleteBuffers(uint _vao, uint _vbo, uint _ebo)
{
	glDeleteVertexArrays(1, &_vao);
	glDeleteBuffers(1, &_vbo);
	glDeleteBuffers(1, &_ebo);
}
void Renderer::DeleteExtraBuffer(int size, uint buffer)
{
	glDeleteBuffers(size, &buffer);
}
void Renderer::BindExtraBuffer(unsigned int buffer, float* data, unsigned int sizeOfData, unsigned int bufferType)
{
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeOfData, data, bufferType);
}
uint Renderer::GetShader() { return programShader; }
void Renderer::SwapBuffers() { glfwSwapBuffers(_window->GetWindow()); }
