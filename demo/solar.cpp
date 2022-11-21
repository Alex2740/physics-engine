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
#include "graphics/vao.h"
#include "graphics/vbo.h"
#include "graphics/ebo.h"
#include "graphics/texture.h"
#include "graphics/camera.h"
#include "graphics/api.h"

const unsigned int width = 800;
const unsigned int height = 800;

// Vertices coordinates
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
	Vector3(0.0f,  0.0f,  0.0f),
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

int main()
{
	float dt = 0.001f;
	PhysicWorld physicWorld = PhysicWorld();

	Vector3 positionCubeFix = Vector3(0.0, 0.0, 0.0);
	RigidBody fixCube = RigidBody(positionCubeFix, 1.0, 1.0, 1.0, 42.69, 1.0f, 1.0f);
	physicWorld.AddRigidBody(&fixCube);

	Vector3 positionFlyingCube = Vector3(0.5, 0.0, 0.0);
	RigidBody flyingCube = RigidBody(positionFlyingCube, 1.0, 1.0, 1.0, 100.0f, 0.9f, 0.9f);
	physicWorld.AddRigidBody(&flyingCube);

	physicWorld.AddForce(&flyingCube, new Force::Gravity(&flyingCube));

	physicWorld.AddForceLocalPoint(&flyingCube, new Force::Spring(&flyingCube, &fixCube, Vector3(-0.5f, 0.5f, 0.5f), Vector3(0.5f, -0.5f, 0.5f), 100.0f), Vector3(-0.5f, 0.5f, 0.5f));
	//physicWorld.AddForceLocalPoint(&flyingCube, new Force::Spring(&flyingCube, &fixCube, Vector3(-0.5f, 0.5f, -0.5f), Vector3(0.5f, -0.5f, -0.5f), 3000.0f), Vector3(-0.5f, 0.5f, -0.5f));

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
	glViewport(-30, 0, width, height);

	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("resources/shaders/default.vert", "resources/shaders/default.frag");

	Matrix4 model = Matrix4::Identity();
	shaderProgram.setMat4("model", model);

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

	// Texture
	Texture brickTex("resources/textures/brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	brickTex.texUnit(shaderProgram, "tex0", 0);
	Texture popCatTex("resources/textures/pop_cat.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	popCatTex.texUnit(shaderProgram, "tex0", 0);

	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);

	// Creates camera object
	Camera camera(width, height, Graphics::Api::Vector3ToOpenGL(Vector3(0.0f, 0.0f, 10.0f)));

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
		// std::cout << flyingCube.getOrientation() << "\n";
		// std::cout << sqrtf(powf(flyingCube.position.x, 2) + powf(flyingCube.position.y, 2)) << std::endl;

		// Updates and exports the camera matrix to the Vertex Shader
		camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();

		glm::mat4 model = glm::mat4(1.0f);
		Vector3 tmp = Vector3(fixCube.position.x, fixCube.position.y, fixCube.position.z - 10);
		model = glm::translate(model, Graphics::Api::Vector3ToOpenGL(tmp));
		Vector3 rotation = fixCube.getOrientation().toEuler();
		
		// Rotation on Z-Axis
		model = glm::rotate(model, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

		// Rotation on Y-Axis
		model = glm::rotate(model, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));

		// Rotation on X-Axis
		model = glm::rotate(model, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));

		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, &model[0][0]);
		brickTex.Bind();
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		tmp = Vector3(flyingCube.position.x, flyingCube.position.y, flyingCube.position.z - 10);
		model = glm::translate(model, Graphics::Api::Vector3ToOpenGL(tmp));

		rotation = flyingCube.getOrientation().toEuler();

		// Rotation on Z-Axis
		model = glm::rotate(model, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

		// Rotation on Y-Axis
		model = glm::rotate(model, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));

		// Rotation on X-Axis
		model = glm::rotate(model, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));

		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, &model[0][0]);
		popCatTex.Bind();
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);

		// Take care of all GLFW events
		glfwPollEvents();
	}

	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	brickTex.Delete();
	shaderProgram.Delete();

	// Delete window before ending the program
	glfwDestroyWindow(window);

	// Terminate GLFW before ending the program
	glfwTerminate();

	return 0;
}