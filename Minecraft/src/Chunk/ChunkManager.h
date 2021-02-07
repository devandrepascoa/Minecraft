#pragma once
#include <vector>
#include <thread>
#include <future>
#include "../Renderers/MasterRenderer.h"
#include <glm/vec2.hpp>
#include <queue>


struct KeyFuncs
{
	size_t operator()(const glm::ivec2& k)const
	{
		return std::hash<int>()(k.x) ^ std::hash<int>()(k.y);
	}

	bool operator()(const glm::ivec2& a, const glm::ivec2& b)const
	{
		return a.x == b.x && a.y == b.y;
	}
};

class ChunkManager
{
private:
	std::unordered_map<glm::ivec2, Chunk*, KeyFuncs, KeyFuncs> chunks;
	std::deque<glm::ivec2> chunksToUpdate;
public:
	ChunkManager();
	~ChunkManager();
	Chunk* getChunk(const glm::vec2& position) const;
	Block* getBlock(const glm::vec3& position) const;
	std::deque<glm::ivec2>& getChunksToUpdate();
	void addChunk(const glm::ivec2& position, Chunk* chunk);
	void addChunkToUpdate(const glm::vec2& position);
	void addChunkToUpdateFromBlock(const glm::vec3& position);
	std::unordered_map<glm::ivec2, Chunk*, KeyFuncs, KeyFuncs> getChunks();
};

