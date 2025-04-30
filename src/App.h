#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "Sphere.h"
#include "Grid.h"
#include "Renderer.h"
#include "TextureLoader.h"
#include "Cube.h"
#include "Skybox.h"

#include "DirectionalLight.h"

#include <iostream>
class App
{
public:
	App() = default;
	~App() = default;

	void Init();
	void Update();
	void Terminate();
	
	const int WindowCheck();
	const int LoadOpenGL();
	void OpenGLSettings();

	void processInput(GLFWwindow* window);
	// Static callback functions
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

	Camera camera;
	GLFWwindow* window;
	Renderer renderer;


private:
	// settings
	const unsigned int SCR_WIDTH = 800;
	const unsigned int SCR_HEIGHT = 600;
	const float aspect = (float)SCR_WIDTH / (float)SCR_HEIGHT;
	float lastX = (float)SCR_WIDTH / 2.0;
	float lastY = (float)SCR_HEIGHT / 2.0;
	bool firstMouse = true;

	// timing
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	// Instance-specific callback handlers
	void instance_framebuffer_size_callback(int width, int height);
	void instance_mouse_callback(double xpos, double ypos);
	void instance_scroll_callback(double yoffset);


};


