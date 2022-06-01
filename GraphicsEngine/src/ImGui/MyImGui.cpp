#include "MyImGui.h"

MyImGui::MyImGui()
{
}

void MyImGui::Init()
{
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
    glsl_version = "#version 100";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
    // GL 3.2 + GLSL 150
    glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    // GL 3.0 + GLSL 130
    glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif
}

void MyImGui::InitAfterWindow(Window* win)
{
    glfwMakeContextCurrent(win->GetWindow());
    glfwSwapInterval(1); // Enable vsync
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(win->GetWindow(), true);
    ImGui_ImplOpenGL3_Init(glsl_version);
    _window = win;
}

void MyImGui::Update()
{

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
    UpdateWindowsOne();
    UpdateWindowsTwo();
    // 3. Show another simple window.
    if (show_another_window)
    {
        ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        ImGui::Text("Hello from another window!");
        if (ImGui::Button("Close Me"))
            show_another_window = false;
        ImGui::End();
    }
}

void MyImGui::Draw()
{
    // Rendering
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(_window->GetWindow(), &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    //glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

MyImGui::~MyImGui()
{
}
ImVec4 clear_color;
void MyImGui::Begin(std::string a){ ImGui::Begin(a.c_str()); }
void MyImGui::End() { ImGui::End(); }
void MyImGui::Text(std::string a) { ImGui::Text(a.c_str()); }
void MyImGui::SliderFloat(std::string a, float * b, float min,float max) { ImGui::SliderFloat(a.c_str(), b, min, max); }
//void MyImGui::SliderFloat3(std::string a,vec3 * b, float min, float max) { ImGui::SliderFloat3(a.c_str(), (float*)&b, min, max); }
void MyImGui::UpdateWindowsTwo()
{
    if (show_demo_window)
        ImGui::ShowDemoWindow(&show_demo_window);

    // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
    {
        static float f = 0.0f;
        static int counter = 0;
        //float* a;
        ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

        ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
        ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
        ImGui::Checkbox("Another Window", &show_another_window);

        //ImGui::SliderFloat("float", &*a, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        //ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color
        //ImGui::ColorEdit3("pos", (float*)(&(*it)->transform.position)); // Edit 3 floats representing a color
        
        int w=0;
        for (std::list<Entity*>::iterator it = Entity::EntitysLists.begin(); it != Entity::EntitysLists.end(); it++)
        {
            vec3 rot = (*it)->transform.eulerAngles;
            vec3 pos = (*it)->transform.position;

            ImGui::SliderFloat3(((*it)->_name + "pos").c_str(), (float*) & pos, -10.0f, 10.0f);
            ImGui::SliderFloat3(((*it)->_name + "rot").c_str(), (float*) &rot, -90.0f, 90.0f);
            (*it)->SetRotations(rot);
            (*it)->SetPos(pos);
            w++;
            ImGui::Checkbox(((*it)->_name + "enabled").c_str(), &(*it)->_enabled);
        }

        for (std::list<Light*>::iterator it = Light::LightsLists.begin(); it != Light::LightsLists.end(); it++)
        {
            vec3 ambient = (*it)->ambient;
            vec3 specular = (*it)->specular;
            vec3 diffuse = (*it)->diffuse;
            ImGui::SliderFloat3(((*it)->_name + "ambient").c_str(), (float*)&ambient, 0.0f, 1.0f);
            ImGui::SliderFloat3(((*it)->_name + "specular").c_str(), (float*)&specular, 0.0f, 1.0f);
            ImGui::SliderFloat3(((*it)->_name + "diffuse").c_str(), (float*)&diffuse, 0.0f, 1.0f);
            (*it)->SetAmbient(ambient);
            (*it)->SetSpecular(specular);
            (*it)->SetDiffuse(diffuse);
        }
        if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
    }
}

void MyImGui::UpdateWindowsOne()
{
    
        static float f = 0.0f;
        static int counter = 0;

        ImGui::Begin("Ventana 2");                    
        for (std::list<Entity*>::iterator it = Entity::EntitysLists.begin(); it != Entity::EntitysLists.end(); it++)
        {
            glm::vec3 a = (*it)->transform.position;
            ImGui::SliderFloat3(((*it)->_name + " pos").c_str(), (float*)&(*it)->transform.position, -10.0f, 10.0f);
            (*it)->SetPos((*it)->transform.position);
        }
        ImGui::End();
    
}

