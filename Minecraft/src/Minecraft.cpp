#include <glad/glad.h> 
#include "GLFW/glfw3.h"
#include <windows.h>
#include <iostream>
#include <string>
#include "Utils.h"
#include "OpenGL/VertexBuffer.h"
#include "OpenGL/VertexArray.h"
#include "Shader.h"
#include "OpenGL/IndexBuffer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"
#include "Renderers/MasterRenderer.h"
#include "Texture.h"

float SCR_WIDTH = 1920;
float SCR_HEIGHT = 1080;
Camera camera(glm::vec3(0.0f, 10.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
bool quad = false;
// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		quad = true;
	else
		quad = false;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void alertError(const char* message) {
	MessageBoxA(NULL, message, "Minecraft", MB_ICONERROR);
}

void frameBufferSizeCallback(GLFWwindow* window, int width, int height) {
	SCR_WIDTH = width;
	SCR_HEIGHT = height;
	GLCall(glViewport(0, 0, width, height));
}

GLFWwindow* initializeOpenglWindow(int startWidth, int startHeight, const char* title) {
	if (!glfwInit()) {
		std::cout << "Failed to initialize glfw" << std::endl;
		return nullptr;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //For macOS window initialization to work


	GLFWwindow* window = glfwCreateWindow(startWidth, startHeight, title, NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to initialize glfw window" << std::endl;
		return nullptr;
	}
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to load GLAD" << std::endl;
		return nullptr;
	}


	return window;
}

void addFaceToMesh(Mesh& mesh, glm::vec3 position, FaceType faceType) {
	const std::array<float, 20>& faceVertices = getFaceVertices(faceType);
	std::vector<float>& vertices = mesh.getVertices();
	std::vector<unsigned int>& indices = mesh.getIndices();
	int numVertices = vertices.size() / 5;
	for (size_t i = 0; i < 20; i += 5) {
		vertices.push_back((float)position.x + faceVertices[i]);
		vertices.push_back((float)position.y + faceVertices[i + 1]);
		vertices.push_back((float)position.z + faceVertices[i + 2]);
		vertices.push_back(faceVertices[i + 3]);
		vertices.push_back(faceVertices[i + 4]);
	}
	indices.push_back(numVertices);
	indices.push_back(numVertices + 1);
	indices.push_back(numVertices + 2);
	indices.push_back(numVertices + 2);
	indices.push_back(numVertices + 3);
	indices.push_back(numVertices);
}


int main()
{
	GLFWwindow* window = initializeOpenglWindow(1920, 1080, "Minecraft");

	if (!window) {
		alertError("Error Loading GLFW window");
		glfwTerminate();
		return -1;
	}

	std::cout << "Opengl Version: " << glGetString(GL_VERSION) << std::endl;


	MasterRenderer renderer;

	Mesh mesh(std::vector<float>(vertices, vertices + sizeof(vertices) / sizeof(float)), std::vector<unsigned int>(indices, indices + sizeof(indices) / sizeof(unsigned int)));
	mesh.clearIndices();
	mesh.clearVertices();
	for (int i = -150; i < 150; i += 3) {
		for (int j = 0; j < 10; j += 3) {
			for (int k = -150; k < 150; k += 3) {
				addFaceToMesh(mesh, glm::vec3(i, j, k), FaceType::BOTTOM);
				addFaceToMesh(mesh, glm::vec3(i, j, k), FaceType::TOP);
				addFaceToMesh(mesh, glm::vec3(i, j, k), FaceType::LEFT);
				addFaceToMesh(mesh, glm::vec3(i, j, k), FaceType::RIGHT);
				addFaceToMesh(mesh, glm::vec3(i, j, k), FaceType::FRONT);
				addFaceToMesh(mesh, glm::vec3(i, j, k), FaceType::BACK);
			}
		}
	}
	Mesh* mesh2 = &mesh;

	mesh.updateBuffers();
	renderer.addMesh(mesh);

	while (!glfwWindowShouldClose(window)) {
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		processInput(window);

		GLCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
		renderer.render(camera);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
