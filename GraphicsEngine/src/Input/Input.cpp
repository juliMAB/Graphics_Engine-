#include "Input.h"
#include "../Internal/Internal.h"

Window*  Input::window = nullptr;
Camera2* Input::mainCam = nullptr;
std::list<int> Input::currentKeysDown = std::list<int>();
char                keys[GLFW_KEY_LAST + 1];

typedef int GLFWbool;
GLFWbool            stickyKeys;
GLFWbool            lockKeyMods;

bool firstMouse = true;

float lastX = 800 / 2.0f;
float lastY = 600 / 2.0f;

struct {
	GLFWwindowposfun          pos;
	GLFWwindowsizefun         size;
	GLFWwindowclosefun        close;
	GLFWwindowrefreshfun      refresh;
	GLFWwindowfocusfun        focus;
	GLFWwindowiconifyfun      iconify;
	GLFWwindowmaximizefun     maximize;
	GLFWframebuffersizefun    fbsize;
	GLFWwindowcontentscalefun scale;
	GLFWmousebuttonfun        mouseButton;
	GLFWcursorposfun          cursorPos;
	GLFWcursorenterfun        cursorEnter;
	GLFWscrollfun             scroll;
	GLFWkeyfun                key;
	GLFWcharfun               character;
	GLFWcharmodsfun           charmods;
	GLFWdropfun               drop;
} callbacks;

#define _GLFW_STICK 3
Input::Input() {}
void Input::Init()
{
	lastX = Input::window->GetWidth() / 2.0f;
	lastY = Input::window->GetHeight() / 2.0f;
	glfwSetInputMode(window->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}
Input::~Input() {}
static int _lastKey,_lastAction;
void Input::mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	//std::cout << "callback_mouse: X:" << xposIn << " Y: " << yposIn << std::endl;
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;
	mainCam->ProcessMouseMovement(xoffset, yoffset);
}

void Input::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		currentKeysDown.push_front(key);
	}
	else if (action == GLFW_RELEASE)
	{
		currentKeysDown.remove(key);
	}
}
void Input::lock_cursor(bool value)
{
	if (value)
		glfwSetInputMode(Input::window->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	else
		glfwSetInputMode(Input::window->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}
int Input::GetKey(int key)
{
	GLFWwindow* window = Input::window->GetWindow();
	int mod = glfwGetKey(window, key);
	assert(window != NULL);
	if (!window)
		return KEY_UNKNOWN;

	if (key < GLFW_KEY_SPACE || key > GLFW_KEY_LAST)
	{
		std::cout << GLFW_INVALID_ENUM << " Invalid key %i : " << key << std::endl;
		return KEY_UNKNOWN;
	}

	if (keys[key] == _GLFW_STICK)
	{
		// Sticky mode: release key now
		keys[key] = GLFW_RELEASE;
		return GLFW_PRESS;
	}
	
	if (keys[key] == GLFW_PRESS)
	{
		keys[key] = 1;
	}
	return (int)keys[key];
}


void Input::StartInputSystem() {
	glfwSetKeyCallback(window->GetWindow(), key_callback);
	glfwSetCursorPosCallback(window->GetWindow(), mouse_callback);
	glfwSetScrollCallback(window->GetWindow(), scroll_callback);
}
bool Input::IsKeyDown(KeyCode keyCode) {
	std::list<int>::iterator it = find(currentKeysDown.begin(), currentKeysDown.end(), keyCode);
	if (it != currentKeysDown.end())
	{
		currentKeysDown.remove(keyCode);
		return true;
	}
	return false;
}
bool Input::IsKeyPressed(KeyCode keyCode) {
	int aux = glfwGetKey(window->GetWindow(), keyCode);
	return aux == GLFW_PRESS;
}
bool Input::IsKeyUp(KeyCode keyCode) {
	int aux = glfwGetKey(window->GetWindow(), keyCode);
	return aux == GLFW_RELEASE;
	
	
	
}

void Input::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	//std::cout << "callback_Scroll: X:" << xoffset << " Y: " << yoffset << std::endl;
	mainCam->ProcessMouseScroll(static_cast<float>(yoffset));
}

void Input::SetWindow(Window* _window) {
	window = _window;
}
void Input::SetCam(Camera2* _cam) {
	mainCam = _cam;
}