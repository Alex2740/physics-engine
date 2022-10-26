// Dear ImGui: standalone example application for GLFW + OpenGL 3, using programmable pipeline
// (GLFW is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan/Metal graphics context creation, etc.)
// If you are new to Dear ImGui, read documentation from the docs/ folder + read the top of imgui.cpp.
// Read online: https://github.com/ocornut/imgui/tree/master/docs

#include "Particule.h"
#include "Vector3.h"
#include "Force.h"
#include "PhysicWorld.h"
#include "contact/ParticleCable.h"
#include "contact/ParticleRod.h"
#include "contact/NaiveParticleContactGenerator.h"
#include "contact/WallContactGenerator.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <stdio.h>
#include <vector>
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

void drawParticle(Particule p, GLfloat r = 255.0, GLfloat g = 0.0, GLfloat b = 0.0)
{
    //glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_POINT_SMOOTH);
    glPointSize(30.0f);
    glBegin(GL_POINTS);
    glVertex3f(p.position.x, p.position.y, p.position.z);
    glColor3f(r, g, b);
    glEnd();

    glFlush();
}

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

int main(int, char**)
{
    float masse = 100;
    float dt = 0.001f;
    float particule_radius = .025f;
    //float particule_radius = .005f;

    Particule b1 = Particule(Vector3(0, -.49f, 0), masse);
    Particule b2 = Particule(Vector3(-.03f, -.55f, 0), masse);
    Particule b3 = Particule(Vector3(.03f, -.55f, 0), masse);
    Particule b4 = Particule(Vector3(-.06f, -.61f, 0), masse);
    Particule b5 = Particule(Vector3(0, -.61f, 0), masse);
    Particule b6 = Particule(Vector3(.06f, -.61f, 0), masse);

    Particule white = Particule(Vector3(0, .5f, 0), masse);

    std::vector<Particule*> listParticles;
    listParticles.push_back(&white);
    listParticles.push_back(&b1);
    listParticles.push_back(&b2);
    listParticles.push_back(&b3);
    listParticles.push_back(&b4);
    listParticles.push_back(&b5);
    listParticles.push_back(&b6);


    PhysicWorld physicWorld = PhysicWorld();

    physicWorld.AddParticule(&b1);
    physicWorld.AddParticule(&b2);
    physicWorld.AddParticule(&b3);
    physicWorld.AddParticule(&b4);
    physicWorld.AddParticule(&b5);
    physicWorld.AddParticule(&b6);
    physicWorld.AddParticule(&white);

    physicWorld.AddForce(&white, new Force::Gravity(&white));

    NaiveParticleContactGenerator* naif = new NaiveParticleContactGenerator(listParticles, particule_radius);
    physicWorld.AddContactGenerator(naif);

    WallContactGenerator* bottom_wall = new WallContactGenerator(listParticles, Vector3(0, 1, 0), Vector3(0, -.8f, 0), particule_radius);
    physicWorld.AddContactGenerator(bottom_wall);

    WallContactGenerator* top_wall = new WallContactGenerator(listParticles, Vector3(0, -1, 0), Vector3(0, .8f, 0), particule_radius);
    physicWorld.AddContactGenerator(top_wall);

    WallContactGenerator* right_wall = new WallContactGenerator(listParticles, Vector3(-1, 0, 0), Vector3(.8f, 0, 0), particule_radius);
    physicWorld.AddContactGenerator(right_wall);

    WallContactGenerator* left_wall = new WallContactGenerator(listParticles, Vector3(1, 0, 0), Vector3(-.8f, 0, 0), particule_radius);
    physicWorld.AddContactGenerator(left_wall);

    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
    const char* glsl_version = "#version 100";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
    // GL 3.2 + GLSL 150
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

    // Create window with graphics context
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Physic Engine Demo", NULL, NULL);

    if (window == NULL)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Our state
    ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    float base_force = 10000;

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        physicWorld.RunPhysics(dt);

        drawParticle(b1, 255, 255, 0);
        drawParticle(b2, 0, 0, 255);
        drawParticle(b3, 255, 0, 0);
        drawParticle(b4, 100, 0, 200);
        drawParticle(b5, 200, 100, 0);
        drawParticle(b6, 0, 255, 0);

        drawParticle(white, 255, 255, 255);

        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}