#pragma once
#include <glad/glad.h> 
#include "GLFW/glfw3.h"
#include "Camera.h"
#include "Renderers/MasterRenderer.h"
#include "Chunk/Chunk.h"
#include "Entities/Player.h"
#include "Chunk/ChunkManager.h"

class Application
{
private:
	int windowWidth, windowHeight;
	bool running;
	float lastFrameTime, lastFrame;
	GLFWwindow* window;
	MasterRenderer* renderer;
	Player player;
	ChunkManager chunkManager;
	Block* focusBlock;
	std::thread* chunkUpdateThread;
	bool initializeOpenglWindow(const char* title);
	void processKeyboardInput();
	void chunkUpdateTask();
public:
	Application();
	~Application();

	std::mutex threadLock;
	void run();
	static Application& getInstance();
	static void onWindowResize(GLFWwindow* window, int width, int height);
	static void onMouseMoved(GLFWwindow* window, double xPos, double yPos);
	static void onMouseButton(GLFWwindow* window, int button, int action, int mods);
	static void onWindowClose(GLFWwindow* window);
};

