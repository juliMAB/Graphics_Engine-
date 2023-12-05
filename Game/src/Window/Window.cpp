#include "Window.h"
#include <iostream>
Window::Window() {
	_glfWindow = nullptr;
}
Window::~Window() {
    glfwDestroyWindow(_glfWindow);
    _glfWindow = nullptr;
}

void Window::Init(int W, int H,const char* name)
{
	_glfWindow = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, name, NULL, NULL);
    if (_glfWindow == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
}

void Window::PollEvents()
{
    glfwPollEvents();
}

void Window::SwapBuffers()
{
    glfwSwapBuffers(_glfWindow);
}

bool Window::WindowShouldClose()
{
    return glfwWindowShouldClose(_glfWindow);
}

void Window::SelectWindowAtCurrentContext()
{
    glfwMakeContextCurrent(_glfWindow);
}
void Window::SetFramebufferSizeCallback(GLFWframebuffersizefun callback)
{
    glfwSetFramebufferSizeCallback(_glfWindow, callback);
}
