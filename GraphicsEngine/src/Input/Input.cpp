#include "Input.h"
#include "../Internal/Internal.h"

Window*  Input::window = nullptr;
Camera* Input::mainCam = nullptr;
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
	_lastKey = key;
	_lastAction = action;
	std::cout <<"callback: key:" << key << " action: "<< action << std::endl;

	if (key >= 0 && key <= GLFW_KEY_LAST)
	{
		GLFWbool repeated = GLFW_FALSE;

		if (action == GLFW_RELEASE && keys[key] == GLFW_RELEASE)
			return;

		if (action == GLFW_PRESS && keys[key] == GLFW_PRESS)
			repeated = GLFW_TRUE;

		if (action == GLFW_RELEASE && stickyKeys)
			keys[key] = _GLFW_STICK;
		else
			keys[key] = (char)action;

		if (repeated)
			action = GLFW_REPEAT;
	}

	if (!lockKeyMods)
		mods &= ~(GLFW_MOD_CAPS_LOCK | GLFW_MOD_NUM_LOCK);

	if (callbacks.key)
		callbacks.key((GLFWwindow*)window, key, scancode, action, mods);
}
int Input::glfwGetKey(int key)
{
	GLFWwindow* window = Input::window->GetWindow();
	assert(window != NULL);

	if (!window)
	{
		return GLFW_RELEASE;
	}

	if (key < GLFW_KEY_SPACE || key > GLFW_KEY_LAST)
	{
		//_glfwInputError(GLFW_INVALID_ENUM, "Invalid key %i", key);
		std::cout << GLFW_INVALID_ENUM << " Invalid key %i : " << key << std::endl;
		return GLFW_RELEASE;
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
	if (_lastAction == GLFW_PRESS && _lastKey == keyCode)
	{
		//_lastKey = 0;
		return true;
	}
	return false;
}
bool Input::IsKeyPress(KeyCode keyCode) {
	if ((_lastAction == GLFW_PRESS && _lastKey == keyCode))
	{
		return true;
	}
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
void Input::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	std::cout << "callback_Scroll: X:" << xoffset << " Y: " << yoffset << std::endl;
	mainCam->ProcessMouseScroll(static_cast<float>(yoffset));
}

void Input::SetWindow(Window* _window) {
	window = _window;
}
void Input::SetCam(Camera* _cam) {
	mainCam = _cam;
}