#include "ChunkRenderer.h"
#include "../Utilities/Utils.h"
#include <glm/gtc/matrix_transform.hpp>

ChunkRenderer::ChunkRenderer()
	:shader("res/shaders/basic3d.shader"), textureAtlas("res/textures/textureAtlas.png") {
}

void ChunkRenderer::render(const Camera& camera, Chunk& chunk)
{
	GLCall(glEnable(GL_DEPTH_TEST));
	textureAtlas.Bind(0);
	shader.bind();
	shader.setUniformMatrix4FV("view", camera.getViewMatrix());
	shader.setUniformMatrix4FV("projection", glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 10000.0f));
	shader.setUniform1i("texture0", 0);

	chunk.getMesh().getVao().bind();
	chunk.getMesh().getIbo().bind();
	glm::mat4 model = glm::mat4(1.0f);
	glm::vec3 position = chunk.getPosition();
	model = glm::translate(model, position *= 16);
	shader.setUniformMatrix4FV("model", model);

	GLCall(glDrawElements(GL_TRIANGLES, chunk.getMesh().getIbo().getNumIndices(), GL_UNSIGNED_INT, 0));

}
