#include "MasterRenderer.h"

MasterRenderer::MasterRenderer()
	:shader("res/shaders/basic3d.shader"),texture("res/textures/dirt.jpg"){
	texture.Bind(0);
}

void MasterRenderer::addCube(const Cube& cube)
{
	cubeRenderer.addCube(cube);
}

void MasterRenderer::addMesh(Mesh& mesh)
{
	meshes.push_back(std::reference_wrapper<Mesh>(mesh));
}

void MasterRenderer::render(const Camera& camera)
{
	GLCall(glEnable(GL_DEPTH_TEST));

	cubeRenderer.render(camera);

	shader.bind();
	shader.setUniformMatrix4FV("view", camera.GetViewMatrix());
	shader.setUniformMatrix4FV("projection", glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f));
	shader.setUniform1i("texture0", 0);
	for (auto mesh : meshes) {
		mesh.get().getVao().bind();
		mesh.get().getIbo().bind();
		glm::mat4 model = glm::mat4(1.0f);
		shader.setUniformMatrix4FV("model", model);

		GLCall(glDrawElements(GL_TRIANGLES, mesh.get().getIbo().getNumIndices(), GL_UNSIGNED_INT, 0));
	}
}
