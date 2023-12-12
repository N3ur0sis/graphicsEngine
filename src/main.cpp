#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Engine/Engine.h"

//Declaration
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main() {

	//Initialize GLFW 
	if (glfwInit() != GLFW_TRUE) {
		std::cout << "Failed to initialize GLFW" << std::endl;
		return -1;
	}

	// Set GLFW window hints and create the window
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(800, 600, "Graphics Engine", nullptr, nullptr);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	//Fail to init glad if window not current
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//Initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}


	//initilazing engine.
	Engine app(window);
	app.run();


	glfwTerminate();
	return 0;

}


//Callback for opengl 
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}




