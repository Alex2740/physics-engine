#include <filesystem>
namespace fs = std::filesystem;
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include "graphics/shader.h"
#include "graphics/vao.h"
#include "graphics/vbo.h"
#include "graphics/ebo.h"
#include "graphics/texture.h"
#include "graphics/camera.h"
#include "graphics/api.h"

#include<physics/Rigidbody.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

const unsigned int width = 1200;
const unsigned int height = 800;

// Vertices coordinates

GLfloat verticestapis[] =
{ //     COORDINATES     /        COLORS        /    TexCoord    /       NORMALS     //
	-1.0f, 0.0f,  1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
	-1.0f, 0.0f, -1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 1.0f,		0.0f, 1.0f, 0.0f,
	 1.0f, 0.0f, -1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 1.0f,		0.0f, 1.0f, 0.0f,
	 1.0f, 0.0f,  1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 0.0f,		0.0f, 1.0f, 0.0f
};

GLuint indicestapis[] =
{
	0, 1, 2,
	0, 2, 3
};

GLfloat lightVertices[] =
{ //     COORDINATES     //
	-0.1f, -0.1f,  0.1f,
	-0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f,  0.1f,
	-0.1f,  0.1f,  0.1f,
	-0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f,  0.1f
};

GLuint lightIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};


GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	-0.5f, -0.5f, -0.5f,	0.0f, 1.0f, 0.0f,	0.0f, 0.0f,
	0.5f, -0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	1.0f, 0.0f,
	0.5f, 0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	1.0f, 1.0f,
	0.5f, 0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	1.0f, 1.0f,
	-0.5f, 0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,	0.0f, 1.0f, 0.0f,	0.0f, 0.0f,

	-0.5f, -0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	0.0f, 0.0f,
	0.5f, -0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	1.0f, 0.0f,
	0.5f, 0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	1.0f, 1.0f,
	0.5f, 0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	1.0f, 1.0f,
	-0.5f, 0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	0.0f, 1.0f,
	-0.5f, -0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	0.0f, 0.0f,

	-0.5f, 0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	1.0f, 0.0f,
	-0.5f, 0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,	0.0f, 1.0f, 0.0f,	0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,	0.0f, 1.0f, 0.0f,	0.0f, 1.0f,
	-0.5f, -0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	0.0f, 0.0f,
	-0.5f, 0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	1.0f, 0.0f,

	0.5f, 0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	1.0f, 0.0f,
	0.5f, 0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	1.0f, 1.0f,
	0.5f, -0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	0.0f, 1.0f,
	0.5f, -0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	0.0f, 0.0f,
	0.5f, 0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,	0.0f, 1.0f, 0.0f,	0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	1.0f, 1.0f,
	0.5f, -0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	1.0f, 0.0f,
	0.5f, -0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	1.0f, 0.0f,
	-0.5f, -0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,	0.0f, 1.0f, 0.0f,	0.0f, 1.0f,

	-0.5f, 0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	0.0f, 1.0f,
	0.5f, 0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	1.0f, 1.0f,
	0.5f, 0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	1.0f, 0.0f,
	0.5f, 0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	1.0f, 0.0f,
	-0.5f, 0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	0.0f, 0.0f,
	-0.5f, 0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	0.0f, 1.0f
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
};

Vector3 cubePositions[] = {
	Vector3(1.0f,  2.0f,  -1.0f),
	Vector3(2.0f,  5.0f, -15.0f),
	Vector3(-1.5f, -2.2f, -2.5f),
	Vector3(-3.8f, -2.0f, -12.3f),
	Vector3(2.4f, -0.4f, -3.5f),
	Vector3(-1.7f,  3.0f, -7.5f),
	Vector3(1.3f, -2.0f, -2.5f),
	Vector3(1.5f,  2.0f, -2.5f),
	Vector3(1.5f,  0.2f, -1.5f),
	Vector3(-1.3f,  1.0f, -1.5f),
};

static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

int main()
{
	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit())
		return 1;

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


	Vector3 positionCubeFix = Vector3(0.0, 0.0, 0.0);
	RigidBody fixCube = RigidBody(positionCubeFix, 1.0, 1.0, 1.0, 42.69, 1.0f, 1.0f);
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(1280, 720, "Demo", NULL, NULL);
	if (window == NULL)
		return 1;
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Enable vsync

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);


	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();

	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(-30, 0, width, height);

	Shader shadertapis("resources/shaders/default.vert", "resources/shaders/default.frag");

	VAO VAO3;
	VAO3.Bind();
	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO3(verticestapis, sizeof(verticestapis));
	// Generates Element Buffer Object and links it to indices
	EBO EBO3(indicestapis, sizeof(indicestapis));
	// Links VBO attributes such as coordinates and colors to VAO
	VAO3.LinkAttrib(VBO3, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	VAO3.LinkAttrib(VBO3, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO3.LinkAttrib(VBO3, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO3.LinkAttrib(VBO3, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO3.Unbind();
	VBO3.Unbind();
	EBO3.Unbind();


	


	// Shader for light cube
	Shader lightShader("resources/shaders/light.vert", "resources/shaders/light.frag");
	// Generates Vertex Array Object and binds it
	VAO lightVAO;
	lightVAO.Bind();
	// Generates Vertex Buffer Object and links it to vertices
	VBO lightVBO(lightVertices, sizeof(lightVertices));
	// Generates Element Buffer Object and links it to indices
	EBO lightEBO(lightIndices, sizeof(lightIndices));
	// Links VBO attributes such as coordinates and colors to VAO
	lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	// Unbind all to prevent accidentally modifying them
	lightVAO.Unbind();
	lightVBO.Unbind();
	lightEBO.Unbind();



	

	
	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("resources/shaders/default.vert", "resources/shaders/default.frag");


	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));

	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));

	// Links VBO attributes such as coordinates and colors to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 objectPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 objectModel = glm::mat4(1.0f);
	objectModel = glm::translate(objectModel, objectPos);

	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);

	shadertapis.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shadertapis.ID, "model"), 1, GL_FALSE, glm::value_ptr(objectModel));
	glUniform4f(glGetUniformLocation(shadertapis.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shadertapis.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);


	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(objectModel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	
	// Texture


	Texture brickTex("resources/textures/brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	brickTex.texUnit(shaderProgram, "tex0", 0);
	
	Texture popTex("resources/textures/planks.png", GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE);
	popTex.texUnit(shadertapis, "tex0", 0);
	

	

	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);

	// Creates camera object
	Camera camera(width, height, Graphics::Api::Vector3ToOpenGL(Vector3(0.0f, 0.0f, 2.0f)));

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();


		ImGui::Begin("Phase 4        ");                          

		ImGui::Text("Demo          ");    

		ImGui::Text("Données de collisions ");
		ImGui::Button("Start");
		ImGui::SameLine();
		ImGui::Button("Pause");
		ImGui::End();

		ImGui::Render();
		
		
		
		
		glClear(GL_COLOR_BUFFER_BIT);

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Handles camera inputs
		camera.Inputs(window);

		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		shaderProgram.Activate();
		// Updates and exports the camera matrix to the Vertex Shader

		glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		camera.Matrix(shaderProgram, "camMatrix");

		// Binds texture so that is appears in rendering

		brickTex.Bind();


		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();


		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

		shadertapis.Activate();

		glUniform3f(glGetUniformLocation(shadertapis.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		camera.Matrix(shadertapis, "camMatrix");
		
		
		popTex.Bind();
		

		VAO3.Bind();

		
		glDrawElements(GL_TRIANGLES, sizeof(indicestapis) / sizeof(int), GL_UNSIGNED_INT, 0);
		
		
		
		


		lightShader.Activate();
		// Export the camMatrix to the Vertex Shader of the light cube
		camera.Matrix(lightShader, "camMatrix");
		// Bind the VAO so OpenGL knows to use it
		lightVAO.Bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

		

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);

		// Take care of all GLFW events
		glfwPollEvents();
	}

	// Delete all the objects we've created

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	popTex.Delete();
	brickTex.Delete();
	
	shadertapis.Delete();
	shaderProgram.Delete();
	lightVAO.Delete();
	lightVBO.Delete();
	lightEBO.Delete();
	lightShader.Delete();
	VAO3.Delete();
	VBO3.Delete();
	EBO3.Delete();
	
	shadertapis.Delete();

	// Delete window before ending the program
	glfwDestroyWindow(window);

	// Terminate GLFW before ending the program
	glfwTerminate();

	return 0;
}