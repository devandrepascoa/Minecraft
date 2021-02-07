#include "ChunkManager.h"
#include <iostream>
ChunkManager::ChunkManager() {}

ChunkManager::~ChunkManager()
{
	chunks.clear();
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

void ChunkManager::addChunk(const glm::ivec2& position, Chunk* chunk)
{
	chunks[position] = chunk;
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

std::unordered_map<glm::ivec2, Chunk*, KeyFuncs, KeyFuncs> ChunkManager::getChunks()
{
	return chunks;}
