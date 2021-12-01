#include "Input.h"

Window*  Input::window = nullptr;

Input::Input() {}
Input::~Input() {}
static int _lastKey,_lastAction;
void Input::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	_lastKey = key;
	_lastAction = action;
	//std::cout <<"callback: " << action << std::endl;
}
//void Input::CheckClearInputList()
//{
//	for (int i = 0; i < _inputsListSize; i++)
//		if (_inputs[i] != -1)
//			if (glfwGetKey(window->GetWindow(), _inputs[i]) == GLFW_RELEASE)
//				_inputs[i] = -1;
//}
void Input::StartInputSystem() {
	glfwSetKeyCallback(window->GetWindow(), key_callback);
}
bool Input::IsKeyDown(KeyCode keyCode) {
	if (_lastAction == GLFW_PRESS && _lastKey == keyCode)
	{
		_lastKey = 0;
		return true;
	}
	return false;
}
bool Input::IsKeyPress(KeyCode keyCode) {
	if (_lastAction == GLFW_REPEAT && _lastKey == keyCode)
	{
		return true;
	}
	return false;
}
bool Input::IsKeyUp(KeyCode keyCode) {
	if (_lastAction == GLFW_RELEASE && _lastKey == keyCode)
	{
		_lastKey = 0;
		return true;
	}
	else
		return false;
	
	
	
}
void Input::SetWindow(Window* _window) {
	window = _window;
}