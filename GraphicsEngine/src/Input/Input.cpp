#include "Input.h"

Window*  Input::window = nullptr;

Input::Input() {}
Input::~Input() {}
static GLFWwindow* _window;
static const int _inputsListSize = 12;
static int _inputs[_inputsListSize];
void Input::CheckClearInputList()
{
	for (int i = 0; i < _inputsListSize; i++)
		if (_inputs[i] != -1)
			if (glfwGetKey(_window, _inputs[i]) == GLFW_RELEASE)
				_inputs[i] = -1;
}
void Input::StartInputSystem() {
	for (int i = 0; i < _inputsListSize; i++)
		_inputs[i] = -1;
}
bool Input::IsKeyDown(KeyCode keyCode) {
	return glfwGetKey(window->GetWindow(), keyCode) == KEY_PRESS;
}
bool Input::IsKeyRelease(KeyCode keyCode) {
	return glfwGetKey(window->GetWindow(), keyCode) == KEY_HOLD;
}
bool Input::IsKeyUp(KeyCode keyCode) {
	return glfwGetKey(window->GetWindow(), keyCode) == KEY_RELEASE;
}
void Input::SetWindow(Window* _window) {
	window = _window;
}
int Input::GetActualKey()
{
	return glfwGetKey(window->GetWindow(), KEY_P);
}