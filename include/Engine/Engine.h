#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include "Engine/Shader.h"
#include "Engine/Framebuffer.h"
#include "Engine/Renderer.h"

class Engine {
public:
	Engine(GLFWwindow* window);
	~Engine();
	void run();
	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
private:
	GLFWwindow* window;
	Shader shader;
	Renderer renderer;
	Framebuffer frameBuffer;
	ImGuiIO IO;
	void processInput(GLFWwindow* window);
	void initializeImGui();
	void cleanupImGui();

	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 direction;
	bool firstMouse = true;
	float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
	float pitch = 0.0f;
	float lastX = 800.0f / 2.0;
	float lastY = 600.0 / 2.0;
	float fov = 45.0f;
	float deltaTime = 0.0f;	// Time between current frame and last frame
	float lastFrame = 0.0f; // Time of last frame
};