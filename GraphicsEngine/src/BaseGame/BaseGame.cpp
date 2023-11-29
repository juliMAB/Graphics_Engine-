#include "BaseGame.h"

BaseGame::BaseGame() {
	_window = nullptr;
}
BaseGame::~BaseGame() {
	if (_window != nullptr) {
		_window = nullptr;
		delete _window;
	}
}
int BaseGame::Init(int width,int heigth,const char * title ){
	if (!InitEngine(width, heigth, title))
		return -1;
}
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
bool BaseGame::IsRunning() {
	return !glfwWindowShouldClose(_window->GetWindow());
}
void BaseGame::Deinit()
{
	DeinitEngine();
}
void BaseGame::ClearClolor()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}
void BaseGame::EndDraw()
{
	glfwSwapBuffers(_window->GetWindow());
	glfwPollEvents();
}
void BaseGame::EndUpdate()
{
	glfwPollEvents();
}
bool BaseGame::InitEngine(int windowSizeX, int windowSizeY, std::string windowName)
{
	std::cout << "+Init Engine" << std::endl;
	if (!glfwInit())
		return false;
	if (!InitWindow(windowSizeX,windowSizeY,windowName))
		return false;
	if (!InitGlew())
		return false;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	return true;
}
void BaseGame::DeinitEngine()
{
	glfwTerminate();
}
double BaseGame::getCurrentTime()
{
	return glfwGetTime();
}
bool BaseGame::InitGlew() {
	if (glewInit() != GLEW_OK) // tiene que ir despues de la creacion del contexto de glfw si o si
	{
		std::cout << "Glew error" << std::endl;
		return false;
	}
	return true;
}
bool BaseGame::InitWindow(int windowSizeX, int windowSizeY, std::string windowName) {
	_window = new Window(windowSizeX, windowSizeY, windowName);
	if (!_window->GetWindow())
	{
		glfwTerminate();
		delete _window;
		return false;
	}
	_window->Start();
	return true;
}