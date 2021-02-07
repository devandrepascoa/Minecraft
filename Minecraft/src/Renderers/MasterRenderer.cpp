#include "MasterRenderer.h"
#include <glm/gtc/matrix_transform.hpp>
#include "../Application.h"
MasterRenderer::MasterRenderer(){
}

void MasterRenderer::addChunk(Chunk* chunk)
{
	chunks.push_back(chunk);
}

void MasterRenderer::deleteChunk(Chunk* chunk)
{
	chunks.erase(std::remove(chunks.begin(), chunks.end(), chunk), chunks.end());
}

void MasterRenderer::clear()
{
	GLCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void MasterRenderer::render(const Camera& camera)
{
	GLCall(glEnable(GL_DEPTH_TEST));
	for (auto& chunk : chunks) {
		if (!chunk->isBuffered()) {
			chunk->getMesh().updateBuffers();
			chunk->setBuffered(true);
		}

		chunkRenderer.render(camera, chunk);
	}

}
