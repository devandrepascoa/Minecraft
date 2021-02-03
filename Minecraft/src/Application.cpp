#include "Application.h"
#include "Application.h"
#include "Utilities/Utils.h"
#include <iostream>
#include <windows.h>

void Application::onWindowResize(GLFWwindow* window, int width, int height)
{
	Application& app = getInstance();
	app.windowWidth = width;
	app.windowHeight = height;
	app.player.getCamera().updateProjectionMatrix(width, height);
	GLCall(glViewport(0, 0, width, height));
}

void Application::onMouseMoved(GLFWwindow* window, double xPos, double yPos)
{
	Application& app = getInstance();
	glfwSetCursorPos(window, app.windowWidth / 2, app.windowHeight / 2);
	float xMove = xPos - app.windowWidth / 2;
	float yMove = yPos - app.windowHeight / 2;

	glm::vec3 xRotation = app.player.getRotation() + glm::vec3(0.0f, xMove / 10.0f, 0.0f);
	if (xRotation[0] <= 90.0f && xRotation[0] >= -90.0f)
		app.player.setRotation(xRotation);

	glm::vec3 yRotation = app.player.getRotation() + glm::vec3(yMove / 10.0f, 0.0f, 0.0f);
	if (yRotation[0] <= 90.0f && yRotation[0] >= -90.0f)
		app.player.setRotation(yRotation);

}

void Application::onWindowClose(GLFWwindow* window)
{
	Application& app = getInstance();
	app.running = false;
}


void alertError(const char* message) {
	MessageBoxA(NULL, message, "Minecraft", MB_ICONERROR);
}

bool Application::initializeOpenglWindow(const char* title) {
	if (!glfwInit()) {
		std::cout << "Failed to initialize glfw" << std::endl;
		alertError("Error Loading GLFW window");
		return false;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //For macOS window initialization to work


	window = glfwCreateWindow(windowWidth, windowHeight, title, NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to initialize glfw window" << std::endl;
		alertError("Error Loading GLFW window");
		return false;
	}
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetFramebufferSizeCallback(window, Application::onWindowResize);

	glfwSetCursorPosCallback(window, Application::onMouseMoved);

	glfwSetWindowCloseCallback(window, Application::onWindowClose);

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to load GLAD" << std::endl;
		alertError("Error Loading GLFW window");
		return false;
	}

	return true;
}

Application::Application() :running(true), windowWidth(1920), windowHeight(1080), lastFrameTime(0.0f)
{
	if (!initializeOpenglWindow("Minecraft")) {
		running = false;
		return;
	}
	std::cout << "Opengl Version: " << glGetString(GL_VERSION) << std::endl;
	renderer = new MasterRenderer();

	for (int i = -12; i < 12; i++) {
		for (int k = -12; k < 12; k++) {
			Chunk* newChunk = new Chunk(glm::vec3(i, 0, k));
			chunks.push_back(newChunk);
			newChunk->generateChunk();
			newChunk->generateMesh();
			renderer->addChunk(*newChunk);
			std::cout << "Generating Chunk (" << i << "," << k << ")" << std::endl;
		}
	}

}

Application::~Application()
{
	for (auto chunk : chunks)
		delete chunk;
	delete renderer;
	glfwTerminate();
}

void Application::run()
{
	while (running) {
		float currentFrame = glfwGetTime();
		float deltaTime = currentFrame - lastFrameTime;
		lastFrameTime = currentFrame;


		renderer->clear();
		renderer->render(player.getCamera());

		glfwSwapBuffers(window);
		glfwPollEvents();

		processKeyboardInput();
		player.update(deltaTime);
		std::cout << windowWidth << std::endl;
	}
}

Application& Application::getInstance()
{
	static Application app;
	return app;
}

void Application::processKeyboardInput()
{

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		running = false;
	float velocityFactor = 50.0f;
	float playerVelX = 0, playerVelY = 0, playerVelZ = 0;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		playerVelZ = velocityFactor;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		playerVelZ = -velocityFactor;
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		playerVelY = -velocityFactor;
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		playerVelY = velocityFactor;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		playerVelX = velocityFactor;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		playerVelX = -velocityFactor;

	player.setVelocity(glm::vec3(playerVelX, playerVelY, playerVelZ));
}
