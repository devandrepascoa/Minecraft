#pragma once
#include <glad/glad.h> 
#include "GLFW/glfw3.h"
#include "Camera.h"
#include "Renderers/MasterRenderer.h"
#include "Chunk/Chunk.h"
#include "Entities/Player.h"

class Application
{
private:
	int windowWidth, windowHeight;
	bool running;
	float lastFrameTime;
	GLFWwindow* window;
	MasterRenderer* renderer;
	Player player;

	std::vector<Chunk*> chunks;

	bool initializeOpenglWindow(const char* title);
	void processKeyboardInput();
public:
	Application();
	~Application();

	void run();
	static Application& getInstance();
	static void onWindowResize(GLFWwindow* window, int width, int height);
	static void onMouseMoved(GLFWwindow* window,double xPos, double yPos);
	static void onWindowClose(GLFWwindow* window);
};

