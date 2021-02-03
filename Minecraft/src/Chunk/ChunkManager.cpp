#include "ChunkManager.h"

ChunkManager::ChunkManager(){}

void ChunkManager::loadChunks(glm::vec3 position)
{

}

void ChunkManager::loadChunk(const Chunk&)
{
}

const std::vector<Chunk>& ChunkManager::getChunks()
{
	return chunks;
}
