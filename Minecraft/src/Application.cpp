#include "Application.h"
#include "Utilities/Utils.h"
#include <iostream>
#include <windows.h>
#include <glm/gtc/matrix_transform.hpp>
#include "RayCaster.h"
#include <glm/gtx/string_cast.hpp>
Application::Application() :running(true), windowWidth(1920), windowHeight(1080), lastFrameTime(0.0f), player(glm::vec3(10, 200.0f, 10)), lastFrame(0), focusBlock(nullptr)
{
	if (!initializeOpenglWindow("Minecraft")) {
		running = false;
		return;
	}
	std::cout << "Opengl Version: " << glGetString(GL_VERSION) << std::endl;
	renderer = new MasterRenderer();

	chunkManager.loadChunks(renderer);

}

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

void Application::onMouseButton(GLFWwindow* window, int button, int action, int mods)
{
	Application& app = getInstance();
	if (action == GLFW_PRESS) {
		switch (button) {
		case GLFW_MOUSE_BUTTON_LEFT:
			app.player.setPlayerAction(PlayerAction::PLACE);
			break;

		case GLFW_MOUSE_BUTTON_RIGHT:
			app.player.setPlayerAction(PlayerAction::DESTROY);
			break;
		default:
			app.player.setPlayerAction(PlayerAction::NONE);
			break;
		}
	}
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
	glfwSetMouseButtonCallback(window, Application::onMouseButton);
	glfwSetWindowCloseCallback(window, Application::onWindowClose);

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to load GLAD" << std::endl;
		alertError("Error Loading GLFW window");
		return false;
	}

	return true;
}


Application::~Application()
{
	delete renderer;
	glfwTerminate();
}

void Application::run()
{
	RayCaster caster(player.getCamera());
	lastFrameTime = glfwGetTime();
	while (running) {
		float currentFrame = glfwGetTime();
		float deltaTime = currentFrame - lastFrameTime;
		lastFrameTime = currentFrame;
		//while (glfwGetTime() < lastFrame + 1.0 / 60) {}
		//lastFrame += 1.0 / 60;

		std::cout << "Player pos:" << glm::to_string(player.getPosition()) << std::endl;

		renderer->clear();
		renderer->render(player.getCamera());

		glfwSwapBuffers(window);
		glfwPollEvents();

		processKeyboardInput();
		player.update(chunkManager, deltaTime);

		Block* selectedBlock = caster.getSelectedBlock(chunkManager);

		if (selectedBlock != nullptr) {
			if (focusBlock != nullptr)
				focusBlock->setFocus(false);
			if (focusBlock != selectedBlock) {
				if (focusBlock != nullptr)
					chunkManager.addChunkToUpdateFromBlock(focusBlock->getPosition());
				chunkManager.addChunkToUpdateFromBlock(selectedBlock->getPosition());
				focusBlock = selectedBlock;
				focusBlock->setFocus(true);
			}
			if (player.getPlayerAction() == PlayerAction::DESTROY)
				selectedBlock->setType(BlockType::AIR);
			if (player.getPlayerAction() == PlayerAction::PLACE) {
				glm::vec3 selectedBlockPosition = selectedBlock->getPosition();
				selectedBlockPosition.y += 1;
				Block* block = chunkManager.getBlock(selectedBlockPosition);
				if (block != nullptr)
					block->setType(BlockType::STONE);
			}
			if (player.getPlayerAction() != PlayerAction::NONE) {
				chunkManager.addChunkToUpdateFromBlock(selectedBlock->getPosition());
				player.setPlayerAction(PlayerAction::NONE);
			}
		}
		else {
			player.setPlayerAction(PlayerAction::NONE);
			if (focusBlock != nullptr) {
				focusBlock->setFocus(false);
				chunkManager.addChunkToUpdateFromBlock(focusBlock->getPosition());
				focusBlock = nullptr;
			}
		}

		if (!chunkManager.getChunksToUpdate().empty()) {
			auto chunkPosition = chunkManager.getChunksToUpdate().front();
			chunkManager.getChunksToUpdate().pop_front();
			Chunk* newChunk = chunkManager.getChunk(chunkPosition);
			if (newChunk != nullptr) {
				newChunk->generateMesh(chunkManager);
				newChunk->getMesh().updateBuffers();
				renderer->addChunk(*newChunk);
				std::cout << "Update Mesh at Chunk (" << chunkPosition.x << "," << chunkPosition.y << ")" << std::endl;
			}
		}

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
	float accelFactor = 0.8f;
	if (player.isFlying())
		accelFactor = 5.0f;
	glm::vec3 acceleration = player.getAcceleration();

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		acceleration.x += -glm::cos(glm::radians(player.getRotation().y + 90)) * accelFactor;
		acceleration.z += -glm::sin(glm::radians(player.getRotation().y + 90)) * accelFactor;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		acceleration.x += glm::cos(glm::radians(player.getRotation().y + 90)) * accelFactor;
		acceleration.z += glm::sin(glm::radians(player.getRotation().y + 90)) * accelFactor;
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && (player.isFlying() || player.isGrounded())) {
		if (!player.isFlying())
			acceleration.y += accelFactor * 10.0f;
		else
			acceleration.y += accelFactor;
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS && player.isFlying()) {
		if (!player.isFlying())
			acceleration.y -= accelFactor * 10.0f;
		else
			acceleration.y -= accelFactor;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		acceleration += leftVector(player.getRotation()) * accelFactor;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		acceleration += rightVector(player.getRotation()) * accelFactor;

	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
		player.setFlying(!player.isFlying());

	player.setAcceleration(acceleration);
}
