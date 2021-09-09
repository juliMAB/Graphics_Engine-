#include "Renderer.h"
#include <iostream>

Renderer::Renderer() {
	_window = nullptr;
	buffer = 0;
	programShader = NULL;
	VBO = NULL;
	VAO = NULL;
	EBO = NULL;
}
void Renderer::Awake(Window* window) {
	_window = window;
}
void Renderer::Start() {
	float position[6] = {
		-0.5f, -0.5f,
		 0.0f,  0.5f,
		 0.5f, -0.5f
	};
	
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), position, GL_STATIC_DRAW);

	ShadersStart();
}
void Renderer::Load() {
	
	
}
void Renderer::Update() {
	SetClearWindow(1, 1, 1, 1);
	DrawTriangle();
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
void Renderer::ShadersStart() {
	// 1. retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	// ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		// read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure& e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	const char* vertexShaderSource = vertexCode.c_str();
	const char* fragmentShaderSource = fragmentCode.c_str();

	unsigned int vertexShader, fragmentShader;
	SetVertexShader(vertexShader, vertexShaderSource);
	SetFragmentShader(fragmentShader, fragmentShaderSource);
	LinkShaders(vertexShader, fragmentShader);
	SetTriangle();
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
void Renderer::DrawTriangle() {
	/*glUseProgram(programShader);
	glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
	glDrawArrays(GL_TRIANGLES, 0, 3);*/

	glUseProgram(programShader);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	
}
void Renderer::SetTriangle() {
	float vertices[] = {
		 -0.5f, -0.5f,
		  0.5f, -0.5f,
		  0.5f,  0.5f
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 2,  // first Triangle
	};
	
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
void Renderer::SetQuad() {
	float vertices[] = {
		-0.5f, -0.5f, // ╚  
		 0.5f, -0.5f, // ╝
		 0.5f,  0.5f, // ╗
		-0.5f,  0.5f  // ╔
	};
}