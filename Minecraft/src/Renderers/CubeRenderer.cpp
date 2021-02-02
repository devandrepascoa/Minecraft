#include "CubeRenderer.h"
#include <GLFW/glfw3.h>
#include "../Utils.h"
#include <vector>

CubeRenderer::CubeRenderer()
	:shader("res/shaders/basic3d.shader"), cubeModel(std::vector<float>(vertices, vertices + sizeof(vertices) / sizeof(float)), std::vector<unsigned int>(indices, indices + sizeof(indices) / sizeof(unsigned int))) {
}

void CubeRenderer::addCube(const Cube& cube)
{
	cubes.push_back(cube);
}

void CubeRenderer::render(const Camera& camera)
{
	//if (quad) {
	//	cubeModel.updateData(std::vector<float>(triangleVertices, triangleVertices + sizeof(triangleVertices) / sizeof(float)), std::vector<unsigned int>(triangleIndices, triangleIndices + sizeof(triangleIndices) / sizeof(unsigned int)));
	//	cubeModel.updateBuffers();
	//}
	//else {

	//}
	cubeModel.getVao().bind();
	cubeModel.getIbo().bind();

	shader.bind();
	shader.setUniformMatrix4FV("view", camera.GetViewMatrix());
	shader.setUniformMatrix4FV("projection", glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f));
	for (auto cube : cubes) {
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, cube.getPosition());
		shader.setUniformMatrix4FV("model", model);

		GLCall(glDrawElements(GL_TRIANGLES, cubeModel.getIbo().getNumIndices(), GL_UNSIGNED_INT, 0));
	}
}
