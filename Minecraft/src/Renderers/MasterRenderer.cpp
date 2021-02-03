#include "MasterRenderer.h"
#include <glm/gtc/matrix_transform.hpp>
MasterRenderer::MasterRenderer()
	:shader("res/shaders/basic3d.shader"), texture("res/textures/dirt.jpg") {
	texture.Bind(0);
}

void MasterRenderer::addMesh(Mesh& mesh)
{
	meshes.push_back(std::ref(mesh));
}

void MasterRenderer::addChunk(Chunk& chunk)
{
	chunks.push_back(chunk);
}

void MasterRenderer::clear()
{
	GLCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void MasterRenderer::render(const Camera& camera)
{
	GLCall(glEnable(GL_DEPTH_TEST));
	for (auto chunk : chunks) {
		chunkRenderer.render(camera, chunk);
	}
	shader.bind();
	shader.setUniformMatrix4FV("view", camera.getViewMatrix());
	shader.setUniformMatrix4FV("projection", glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 10000.0f));
	shader.setUniform1i("texture0", 0);
	for (auto mesh : meshes) {
		mesh.get().getVao().bind();
		mesh.get().getIbo().bind();
		glm::mat4 model = glm::mat4(1.0f);
		shader.setUniformMatrix4FV("model", model);

		GLCall(glDrawElements(GL_TRIANGLES, mesh.get().getIbo().getNumIndices(), GL_UNSIGNED_INT, 0));
	}
}
