#include "MyImGui.h"
namespace JuliEngine
{

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

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    UpdateMainWindows();
    if (ShowEntity2List)
    {
        UpdateWindowsEntity2();
    }
    if (ShowLightsList)
    {
        UpdateWindowsLights();
    }
}

void MyImGui::Draw()
{
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(_window->GetWindow(), &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    
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
bool MyImGui::SliderFloat3(std::string a,vec3 * b, float min, float max) 
{
    return ImGui::SliderFloat3(a.c_str(), (float*)&b, min, max); 
}

void MyImGui::UpdateMainWindows()
{
    ImGui::Begin("Ventana de configuracion By juli");
    if (ImGui::Button("ENTITY2",ImVec2(ImGui::GetWindowWidth(),20)))
    {
        ShowEntity2List = !ShowEntity2List;
    }
    if (ImGui::Button("LIGHTS", ImVec2(ImGui::GetWindowWidth(), 20)))
    {
        ShowLightsList = !ShowLightsList;
    }

    ImGui::End();
}
void MyImGui::UpdateWindowsEntity2()
{
    ImGui::Begin("Entity2");
    if (Entity2::EntitysLists.size()>0)
    {
        for (std::list<Entity2*>::iterator it = Entity2::EntitysLists.begin(); it != Entity2::EntitysLists.end(); it++)
        {
            bool enabled = (*it)->getactive();
            if (ImGui::Checkbox(((*it)->getName() + "enabled").c_str(), &enabled))
                (*it)->setActive(enabled);
            if ((*it)->getactive())
            {
                glm::vec3 pos = (* it)->getPos();
                glm::vec3 rot = (*it)->getRot();
                glm::vec3 scale = (**it).getScale();
                if (ImGui::SliderFloat3(((*it)->getName() + " pos").c_str(), (float*)&pos, -10.0f, 10.0f))
                    (**it).SetPos(pos);
                if( ImGui::SliderFloat3(((*it)->getName() + " rot").c_str(), (float*)&rot, -10.0f, 10.0f))
                    (**it).SetRotations(rot);
                if (ImGui::SliderFloat3(((*it)->getName() + " scl").c_str(), (float*)&scale, -10.0f, 10.0f))
                    (**it).SetScale(scale);
            }
        }
    }
    ImGui::End();
}
void MyImGui::UpdateWindowsLights()
{
    for (std::list<Light*>::iterator it = Light::LightsLists.begin(); it != Light::LightsLists.end(); it++)
    {
        bool enabled = (*it)->getactive();
        if (ImGui::Checkbox(((*it)->getName() + "enabled").c_str(), &enabled))
            (*it)->setActive(enabled);
        if ((*it)->getactive())
        {
            glm::vec3 amb = (*it)->GetAmbient();
            glm::vec3 dif = (*it)->GetDiffuse();
            glm::vec3 spe = (*it)->GetSpecular();
            if (ImGui::SliderFloat3(((*it)->getName() + " amb").c_str(), (float*)&amb, -10.0f, 10.0f))
                (**it).SetAmbient(amb);
            if (ImGui::SliderFloat3(((*it)->getName() + " dif").c_str(), (float*)&dif, -10.0f, 10.0f))
                (**it).SetDiffuse(dif);
            if (ImGui::SliderFloat3(((*it)->getName() + " spe").c_str(), (float*)&spe, -10.0f, 10.0f))
                (**it).SetSpecular(spe);
        }
    }
}
}
