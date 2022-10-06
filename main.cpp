// Dear ImGui: standalone example application for GLFW + OpenGL 3, using programmable pipeline
// (GLFW is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan/Metal graphics context creation, etc.)
// If you are new to Dear ImGui, read documentation from the docs/ folder + read the top of imgui.cpp.
// Read online: https://github.com/ocornut/imgui/tree/master/docs

#include "engine/Particule.h"
#include "engine/Vector3.h"
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

struct ColoredParticule {
    Particule particule;
    int red = 255;
    int green = 255;
    int blue = 255;
};

void drawParticle(ColoredParticule cp)
{   
    glEnable(GL_POINT_SMOOTH);
    glPointSize(10.0f);
    glBegin(GL_POINTS);
    glVertex3f(cp.particule.position.x, cp.particule.position.y, cp.particule.position.z);
    glColor3f(cp.red, cp.green, cp.blue); 
    glEnd();

    glFlush();
}

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

int main(int, char**)
{
    float g = 10;
    float dt = 0.001f;

    std::vector<ColoredParticule> particules = {};

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

        {
            ImGui::Begin("Shooter !");

            ImGui::Text("Choose the projectile.");

            if (ImGui::Button("Dirt")) {
                ColoredParticule cp;
                cp.particule = Particule(Vector3(-1, -0.9f, 0), 5);
                particules.push_back(cp);
                Vector3 forces = Vector3(base_force, -g * cp.particule.masse() + base_force, 0);
                cp.particule.integrate(forces, dt);
            }

            if (ImGui::Button("Paper")) {
                ColoredParticule cp;
                cp.particule = Particule(Vector3(-1, -0.9f, 0), 3.5),
                particules.push_back(cp);
                Vector3 forces = Vector3(base_force, -g * cp.particule.masse() + base_force, 0);
                cp.particule.integrate(forces, dt);
            }

            if (ImGui::Button("Steel")) {
                ColoredParticule cp;
                cp.particule = Particule(Vector3(-1, -0.9f, 0), 10);
                particules.push_back(cp);
                Vector3 forces = Vector3(base_force, -g * cp.particule.masse() + base_force, 0);
                cp.particule.integrate(forces, dt);
            }

            ImGui::End();
        }

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        for (int i = 0; i < particules.size(); i++)
        {
            ColoredParticule cp = particules[i];

            if (cp.particule.position.y < -1.2) {
                particules.erase(particules.begin() + i);
            }

            Vector3 gravity = Vector3(0, -g * cp.particule.masse(), 0);
            cp.particule.integrate(gravity, dt);

            drawParticle(cp);
        }

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
