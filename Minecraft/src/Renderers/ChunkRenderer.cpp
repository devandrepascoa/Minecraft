#include "ChunkRenderer.h"
#include "../Utilities/Utils.h"
#include <glm/gtc/matrix_transform.hpp>

ChunkRenderer::ChunkRenderer()
	:shader("res/shaders/basic3d.shader"), textureAtlas("res/textures/textureAtlas.png") {
}

void ChunkRenderer::render(const Camera& camera, Chunk* chunk)
{
	GLCall(glEnable(GL_CULL_FACE));
	GLCall(glCullFace(GL_BACK));
	GLCall(glEnable(GL_DEPTH_TEST));
	textureAtlas.Bind(0);
	shader.bind();
	shader.setUniformMatrix4FV("view", camera.getViewMatrix());
	shader.setUniformMatrix4FV("projection", camera.getProjectionMatrix());
	shader.setUniform1i("texture0", 0);

	chunk->getMesh().getVao()->bind();
	chunk->getMesh().getIbo()->bind();
	glm::mat4 model = glm::mat4(1.0f);
	glm::vec3 position = chunk->getPosition();
	model = glm::translate(model, position *= 16);
	shader.setUniformMatrix4FV("model", model);

	GLCall(glDrawElements(GL_TRIANGLES, chunk->getMesh().getIbo()->getNumIndices(), GL_UNSIGNED_INT, 0));
	GLCall(glDisable(GL_CULL_FACE));
}
