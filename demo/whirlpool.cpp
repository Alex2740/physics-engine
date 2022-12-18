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

#include <cstdlib>

const unsigned int width = 1080;
const unsigned int height = 720;

int main()
{
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

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();

		// Handles camera inputs
		camera.Inputs(window);

		physicWorld.RunPhysics(dt);
		timer += dt;

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

	// Delete window before ending the program
	glfwDestroyWindow(window);

	// Terminate GLFW before ending the program
	glfwTerminate();

	return 0;
}