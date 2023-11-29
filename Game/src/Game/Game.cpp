#include "Game.h"

#include <iostream>
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

Game::Game() { 
    if (_windows != nullptr)
        for (int i = 0; i < MAX_WINDOWS; i++)
            _windows[i] = nullptr;
}
Game::~Game() {

}
int Game::Init() {
    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;

    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    if (_windows == nullptr)
        return -1;

    for (int i = 0; i < MAX_WINDOWS; i++)
    {
        GLFWwindow*& window = _windows[i];
        window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
        if (window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return -1;
        }
        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    }

    // glfw window creation
    // --------------------
    


    // glew: load all OpenGL function pointers
    // ---------------------------------------
    if (glewInit() != GLEW_OK) // tiene que ir despues de la creacion del contexto de glfw si o si
    {
        std::cout << "Glew error" << std::endl;
        return -1;
    }
return 0;
}

int Game::Deinit() {
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}
void Game::Update()
{	
    // input
        // -----
    for (int i = 0; i < MAX_WINDOWS; i++)
    {
        GLFWwindow* window = _windows[i];
		if (window == nullptr)
			continue;
		processInput(window);
    }

    // render
    // ------
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    // -------------------------------------------------------------------------------
    for (int i = 0; i < MAX_WINDOWS; i++)
    {
        GLFWwindow* window = _windows[i];
        if (window == nullptr)
            continue;
        glfwSwapBuffers(window);
    }

    glfwPollEvents();
}
void Game::Draw() {
	
}
bool Game::IsRunning() {

    bool running = false;
    for (int i = 0; i < MAX_WINDOWS; i++)
    {
        GLFWwindow* window = _windows[i];
        if (window == nullptr)
            continue;
        if (!glfwWindowShouldClose(window))
        {
            return true;
        }
    }

	return running;
}
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}