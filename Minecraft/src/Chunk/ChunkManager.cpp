#include "ChunkManager.h"
#include <thread>
#include <future>
#include <iostream>
ChunkManager::ChunkManager() {}

ChunkManager::~ChunkManager()
{
	chunks.clear();
}

void ChunkManager::loadChunks(MasterRenderer* renderer)
{
	constexpr int renderDistance = 2;
	for (int x = -renderDistance; x < renderDistance; x++) {
		for (int y = -renderDistance; y < renderDistance; y++) {
			Chunk* newChunk = new Chunk(glm::vec3(x, 0, y));
			newChunk->generateChunk();
			chunks[glm::ivec2(x, y)] = newChunk;
			addChunkToUpdate(glm::ivec2(x, y));
			std::cout << "Generating Chunk (" << x << "," << y << ")" << std::endl;
		}
	}

}

void ChunkManager::createChunk(MasterRenderer* renderer, const glm::vec2& position)
{
}

Chunk* ChunkManager::getChunk(const glm::vec2& position) const
{
	auto chunk = chunks.find(position);
	return (chunk == chunks.end()) ?
		nullptr : chunk->second;
}
template<typename T>
T mod(T a, T b)
{
	return (a % b + b) % b;
}
Block* ChunkManager::getBlock(const glm::vec3& position) const
{
	glm::vec2 chunkPosition = glm::vec2(glm::floor(position.x / 16.0f), glm::floor(position.z / 16.0f));

	Chunk* chunk = getChunk(chunkPosition);
	glm::vec3 blockPosition = glm::vec3(
		mod((int)position.x, 16),
		position.y,
		mod((int)position.z, 16)
	);

	return (chunk == nullptr) ? nullptr : chunk->getBlock(blockPosition);
}

std::deque<glm::ivec2>& ChunkManager::getChunksToUpdate()
{
	return chunksToUpdate;
}

struct comp
{
	comp(const glm::ivec2& input) : _input(input) {}
	bool operator()(const glm::ivec2& v)
	{
		return v.x == _input.x && v.y == _input.y;
	}
	glm::ivec2 _input;
};
void ChunkManager::addChunkToUpdate(const glm::vec2& position)
{
	if (std::find_if(chunksToUpdate.begin(), chunksToUpdate.end(), comp(position)) == chunksToUpdate.end()) {
		chunksToUpdate.push_back(position);
	}
}

void ChunkManager::addChunkToUpdateFromBlock(const glm::vec3& position)
{
	glm::vec2 selectedBlockChunkPosition =
		glm::vec2(glm::floor(position.x / 16.0f),
			glm::floor(position.z / 16.0f));
	addChunkToUpdate(selectedBlockChunkPosition);
}
