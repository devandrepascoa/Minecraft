#pragma once
#include "../Camera.h"
#include "../Entities/Mesh.h"
#include "../OpenGL/Texture.h"
#include "../OpenGL/Shader.h"
#include "../Chunk/Chunk.h"
#include "ChunkRenderer.h"

class MasterRenderer {
private:
	ChunkRenderer chunkRenderer;
	std::vector<Chunk*> chunks;
public:
	MasterRenderer();
	void addChunk(Chunk* chunk);
	void deleteChunk(Chunk* chunk);
	void clear();
	void render(const Camera& camera);
};
