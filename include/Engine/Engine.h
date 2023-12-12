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
private:
	GLFWwindow* window;
	Shader shader;
	Renderer renderer;
	Framebuffer frameBuffer;
	ImGuiIO IO;
	void processInput();
	void initializeImGui();
	void cleanupImGui();
};