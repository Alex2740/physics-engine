#include <filesystem>
namespace fs = std::filesystem;
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include "physics/PhysicWorld.h"
#include "physics/Rigidbody.h"

#include "graphics/shader.h"
#include "graphics/texture.h"
#include "graphics/camera.h"
#include "graphics/api.h"
#include "graphics/renderer.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include <cstdlib>

const unsigned int width = 1920;
const unsigned int height = 1080;


bool runPhysics = true;

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
		runPhysics = true;
	}
}

int main()
{
	Contact contactToDisplay = Contact::ContactNull();

	float dt = 0.001f;
	
	float timer = 0;
	float timeBetweenSpawn = .5f;
	float maxFallingCube = 20;
	float fallingCube = 0;

	PhysicWorld physicWorld = PhysicWorld();

	RigidBody bar = RigidBody(
		Vector3(0.0f, 0.0f, 0.0f),
		Vector3(5.0f, .5f, .5f),
		1.0f,
		.9f, .8f
	);
	bar.inverseMasse = 0;
	physicWorld.AddRigidBody(&bar);

	physicWorld.AddForceLocalPoint(&bar, new Force::FixAngleForce(&bar, Vector3(-1, 0, 0), Vector3(0, .4f, 0)), Vector3(-1, 0, 0));
	physicWorld.AddForceLocalPoint(&bar, new Force::FixAngleForce(&bar, Vector3(1, 0, 0), Vector3(0, -.4f, 0)), Vector3(1, 0, 0));

	// Initialize GLFW
	glfwInit();

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

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(width, height, "Demo", NULL, NULL);

	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

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

	//Load GLAD so it configures OpenGL
	gladLoadGL();

	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, width, height);

	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("resources/shaders/default.vert", "resources/shaders/default.frag");

	Matrix4 model = Matrix4::Identity();
	shaderProgram.setMat4("model", model);

	Renderer renderer = Renderer();

	// Texture
	Texture brickTex("resources/textures/brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	brickTex.texUnit(shaderProgram, "tex0", 0);
	Texture iceTex("resources/textures/ice.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	iceTex.texUnit(shaderProgram, "tex0", 0);

	renderer.BindTexture(&bar, &brickTex);

	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);

	// Creates camera object
	//Camera camera(width, height, Graphics::Api::Vector3ToOpenGL(Vector3(0.0f, 2.0f, 5.0f)));
	Camera camera(width, height, Graphics::Api::Vector3ToOpenGL(Vector3(0.0f, 0.0f, 5.0f)));

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		glfwPollEvents();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();

		ImGui::NewFrame();
		{
			ImGui::Begin("Contact Details");
			if (contactToDisplay.type != ContactType::ContactNull) {
				char buffer[100] = "Type: ";
				char b[1];
				char buffNumber[100];
				strcat_s(buffer, "BoxBox");
				ImGui::Text(buffer);

				strcpy_s(buffer, "ID Body 1: ");
				strcat_s(buffer, itoa(contactToDisplay.body[0]->getId(), b, 10));
				ImGui::Text(buffer);

				strcpy_s(buffer, "ID Body 2: ");
				strcat_s(buffer, itoa(contactToDisplay.body[1]->getId(), b, 10));
				ImGui::Text(buffer);

				strcpy_s(buffer, "Position: ");
				strcat_s(buffer, contactToDisplay.contactPoint.toString());
				ImGui::Text(buffer);

				strcpy_s(buffer, "Normal: ");
				strcat_s(buffer, contactToDisplay.contactNormal.toString());
				ImGui::Text(buffer);

				strcpy_s(buffer, "Penetration: ");
				sprintf(buffNumber, "%f", contactToDisplay.penetration);
				strcat_s(buffer, buffNumber);
				ImGui::Text(buffer);

				strcpy_s(buffer, "Restitution: ");
				sprintf(buffNumber, "%f", contactToDisplay.restitution);
				strcat_s(buffer, buffNumber);
				ImGui::Text(buffer);

				strcpy_s(buffer, "Friction: ");
				sprintf(buffNumber, "%f", contactToDisplay.friction);
				strcat_s(buffer, buffNumber);
				ImGui::Text(buffer);
			}
			else {
				ImGui::Text("No Contact");
			}
			ImGui::End();
		}

		// Rendering
		ImGui::Render();

		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();

		// Handles camera inputs
		//camera.Inputs(window);

		if (runPhysics) {
			contactToDisplay = physicWorld.RunPhysics(dt);

			if (contactToDisplay.type != ContactType::ContactNull) {
				runPhysics = false;
			}

			timer += dt;
		}

		if (fallingCube < maxFallingCube && timer >= timeBetweenSpawn) {
			float xPos = ((rand() % 200 - 100) / 100.0f); // -1 <> 1
			xPos *= 2.5f; // -5 <> 5
			RigidBody* fallingBox = new RigidBody(
				Vector3(xPos, 5.0f, 0.0f),
				Vector3(.5f, .5f, .5f),
				.05f,
				.9f, .8f
			);
			physicWorld.AddRigidBody(fallingBox);
			physicWorld.AddForce(fallingBox, new Force::Gravity(fallingBox));
			renderer.BindTexture(fallingBox, &iceTex);

			fallingCube += 1;
			timer -= timeBetweenSpawn;
		}

		for each (RigidBody * rb in physicWorld.GetRigidBodies())
		{
			if (rb->position.y < -10) {
				physicWorld.DeleteRigidBody(rb);
				fallingCube -= 1;
			}
		}
		
		// Updates and exports the camera matrix to the Vertex Shader
		camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

		for each (RigidBody* rb in physicWorld.GetRigidBodies())
		{
			renderer.RenderCube(rb, shaderProgram);
		}

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);

		// Take care of all GLFW events
		glfwPollEvents();
	}

	renderer.Delete();
	
	brickTex.Delete();
	shaderProgram.Delete();

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	// Delete window before ending the program
	glfwDestroyWindow(window);

	// Terminate GLFW before ending the program
	glfwTerminate();

	return 0;
}