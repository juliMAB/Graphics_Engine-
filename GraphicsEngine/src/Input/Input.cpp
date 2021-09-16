#include "Input.h"

Window*  Input::window = nullptr;

Input::Input() {}
Input::~Input() {}

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