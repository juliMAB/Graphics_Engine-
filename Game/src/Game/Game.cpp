#include "Game.h"
#include <iostream>
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void processInput(GLFWwindow* window);

Game::Game() { 
    _window = nullptr;
}
Game::~Game() {
    if (_window != nullptr) delete(_window); _window = nullptr;
}
int GLFWINIT()
{
    // glfw: initialize and configure
    // ------------------------------
    if (glfwInit() == GLFW_FALSE) return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    return 0;
}

int GLEWINIT()
{
    // glew: load all OpenGL function pointers
    // ---------------------------------------
    if (glewInit() != GLEW_OK) // tiene que ir despues de la creacion del contexto de glfw si o si
    {
        std::cout << "Glew error" << std::endl;
        return -1;
    }
    return 0;
}
int Game::WINDOWINIT()
{
    _window = new Window();
    _window->Init(600, 600, "name");
    _window->SelectWindowAtCurrentContext();
    _window->SetFramebufferSizeCallback(framebuffer_size_callback);
    return 0;
}
int Game::WINDOWDEINIT()
{
    if (_window == nullptr) return 0;
    delete(_window);
    _window = nullptr;
}

int Game::Init() {
    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;

    if (GLFWINIT() == -1) return -1;

    if (WINDOWINIT() == -1) return -1;

    if (GLEWINIT() == -1) return -1;

    
return 0;
}
int Game::Deinit() {
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    WINDOWDEINIT();
    return 0;
}
void Game::Update()
{	
    //ProcessInput;

    // render
    // ------
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    _window->SwapBuffers();

    _window->PollEvents();
}
void Game::Draw() {
	
}
bool Game::IsRunning() {

    return !_window->WindowShouldClose();
}
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}