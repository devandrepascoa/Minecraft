#pragma once
#include <vector>
#include "Chunk.h"
#include <thread>
#include <future>
class ChunkManager
{
private:
	std::vector<Chunk> chunks;
public:
	ChunkManager();
	void loadChunks(glm::vec3 position);
	void loadChunk(const Chunk&);
	const std::vector<Chunk>& getChunks();
};

