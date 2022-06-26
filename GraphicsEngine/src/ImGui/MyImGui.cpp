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

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    UpdateMainWindows();
    if (ShowEntity2List)
    {
        UpdateWindowsEntity2();
    }
    if (ShowModelList)
    {
        UpdateWindowsModel();
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
    if (ImGui::Button("MODEL", ImVec2(ImGui::GetWindowWidth(), 20)))
    {
        ShowModelList = !ShowModelList;
    }
    ImGui::End();
}
void MyImGui::UpdateWindowsTwo()
{

                              // Create a window called "Hello, world!" and append into it.
    ImGui::Text("Entitys");
    for (std::list<Entity*>::iterator it = Entity::EntitysLists.begin(); it != Entity::EntitysLists.end(); it++)
    {
        vec3 rot = (*it)->transform.eulerAngles;
        vec3 pos = (*it)->transform.position;
        vec3 sca = (*it)->transform.scale;
        
        if(ImGui::SliderFloat3(((*it)->_name + "pos").c_str(), (float*)&pos, -10.0f, 10.0f))
        {
            (*it)->SetPos(pos);
        }
        if (ImGui::SliderFloat3(((*it)->_name + "rot").c_str(), (float*)&rot, -90.0f, 90.0f))
        {
            (*it)->SetRotations(rot);
        }
        if (ImGui::SliderFloat3(((*it)->_name + "sca").c_str(), (float*)&sca, 0.1f, 2.0f))
        {
            (*it)->SetScale(sca);
        }

        ImGui::Checkbox(((*it)->_name + "enabled").c_str(), &(*it)->_enabled);
    }
    ImGui::Text("Lights");
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
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();
}
using namespace JuliEngine;

void baseEntity2Edit(Entity2* it)
{
    bool enabled = (it)->getactive();
    if (ImGui::Checkbox(((it)->getName() + "enabled").c_str(), &enabled))
        (it)->setActive(enabled);
    if ((it)->getactive())
    {
        vec3 pos = (it)->getPos();
        vec3 rot = (it)->getRot();
        vec3 scale = (it)->getScale();
        vec3 color = (it)->getColor();
        if (ImGui::SliderFloat3(((it)->getName() + " pos").c_str(), (float*)&pos, -10.0f, 10.0f))
            (it)->SetPos(pos);
        if (ImGui::SliderFloat3(((it)->getName() + " rot").c_str(), (float*)&rot, -10.0f, 10.0f))
            (it)->SetRotations(rot);
        if (ImGui::SliderFloat3(((it)->getName() + " scl").c_str(), (float*)&scale, -10.0f, 10.0f))
            (it)->SetScale(scale);
        if (ImGui::SliderFloat3(((it)->getName() + " clr").c_str(), (float*)&color, -10.0f, 10.0f))
            (it)->SetColor(color);
    }
}
void baseLight2Edit(Light* it)
{
    vec3 amb = (it)->GetAmbient();
    vec3 dif = (it)->GetDiffuse();
    vec3 spe = (it)->GetSpecular();
    //if (ImGui::SliderFloat3(((it)->getName() + " pos").c_str(), (float*)&pos, -10.0f, 10.0f))
    //    (it)->SetPos(pos);
    //if (ImGui::SliderFloat3(((it)->getName() + " rot").c_str(), (float*)&rot, -10.0f, 10.0f))
    //    (it)->SetRotations(rot);
    //if (ImGui::SliderFloat3(((it)->getName() + " scl").c_str(), (float*)&scale, -10.0f, 10.0f))
    //    (it)->SetScale(scale);
    //if (ImGui::SliderFloat3(((it)->getName() + " clr").c_str(), (float*)&color, -10.0f, 10.0f))
    //    (it)->SetColor(color);
}

void MyImGui::UpdateWindowsEntity2()
{
    ImGui::Begin("Entity2");
    if (Entity2::EntitysLists.size()>0)
    {
        for (std::list<Entity2*>::iterator it = Entity2::EntitysLists.begin(); it != Entity2::EntitysLists.end(); it++)
        {
            baseEntity2Edit(*it);
        }
    }
    ImGui::End();
}
void MyImGui::UpdateWindowsModel()
{
    ImGui::Begin("MODEL");
    if (Model2::listModel.size()>0)
    {
        for (std::list<Model2*>::iterator it = Model2::listModel.begin(); it != Model2::listModel.end(); it++)
        {
            baseEntity2Edit(*it);
            if ((*it)->nodes.size()>0)
            {
                ImGui::Text("NODES");
                for (std::list<Entity2*>::iterator it2 = (*it)->nodes.begin(); it2 != (*it)->nodes.end(); it2++)
                    baseEntity2Edit(*it2);
                ImGui::Text("MESHES");
                for (std::list<Mesh2*>::iterator it2 = (*it)->meshes.begin(); it2 != (*it)->meshes.end(); it2++)
                    baseEntity2Edit(*it2);
            }
        }
    }
    ImGui::End();
}

void MyImGui::UpdateWindowsOne()
{
        ImGui::Begin("Ventana 2");                    
        for (std::list<Entity*>::iterator it = Entity::EntitysLists.begin(); it != Entity::EntitysLists.end(); it++)
        {
            glm::vec3 a = (*it)->transform.position;
            ImGui::SliderFloat3(((*it)->_name + " pos").c_str(), (float*)&(*it)->transform.position, -10.0f, 10.0f);
            (*it)->SetPos((*it)->transform.position);
        }
        ImGui::End();
}

