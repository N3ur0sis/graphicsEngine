#include "Engine/Engine.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//Initializing Engine
Engine::Engine(GLFWwindow* window) : window(window), shader("src/Ressources/Shaders/vertex.sh", "src/Ressources/Shaders/fragment.sh")
{
	
	//Initialize other memebr if needed
	renderer.initialize();
	frameBuffer.create();
	initializeImGui();
}


//Clear data
Engine::~Engine()
{
}

void Engine::run()
{

	glEnable(GL_DEPTH_TEST);

	shader.use(); // don't forget to activate/use the shader before setting uniforms
	shader.setInt("texture1", 0);
	
	double lastTime = glfwGetTime();
	int nbFrames = 0;


	//Render loop
	while(!glfwWindowShouldClose(window)) {

		// Measure speed
		double currentTime = glfwGetTime();
		nbFrames++;
		if (currentTime - lastTime >= 1.0) { 
			printf("%f FPS\n", 1/ ((1000.0 / double(nbFrames)) * 0.001));
			nbFrames = 0;
			lastTime += 1.0;
		}




		glfwPollEvents();


		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;
		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), dockspace_flags);
		ImGui::Begin("Toolbox");
		ImGui::Text("Toolbox Content");;
		ImGui::End();
		ImGui::Begin("Scene");
		const float window_width = ImGui::GetContentRegionAvail().x;
		const float window_height = ImGui::GetContentRegionAvail().y;
		frameBuffer.rescale(window_width, window_height);
		glViewport(0, 0, window_width, window_height);
		ImVec2 pos = ImGui::GetCursorScreenPos();
		ImGui::GetWindowDrawList()->AddImage(
			(void*)frameBuffer.getTextureID(),
			ImVec2(pos.x, pos.y),
			ImVec2(pos.x + window_width, pos.y + window_height),
			ImVec2(0, 1),
			ImVec2(1, 0)
		);
		ImGui::End();
		ImGui::Render();

		frameBuffer.bind();

		renderer.bindtex();
		shader.use();

		// create transformations
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);
		model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
		// retrieve the matrix uniform locations
		unsigned int modelLoc = glGetUniformLocation(shader.ID, "model");
		unsigned int viewLoc = glGetUniformLocation(shader.ID, "view");
		// pass  to the shaders 
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
		// best to do outside nigga
		shader.setMat4("projection", projection);

		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);
		renderer.render();
		frameBuffer.unbind();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		if (IO.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}

		glfwSwapBuffers(window);
	}
	cleanupImGui();
	renderer.cleanup();
	frameBuffer.~Framebuffer();
}

void Engine::processInput()
{
}

void Engine::initializeImGui()
{

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	// darkmode ouais ouais ouais 
	ImGui::StyleColorsDark();
	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	// initialize ImGui's glfw/opengl implementation 
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
	IO = io;
}

void Engine::cleanupImGui()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}