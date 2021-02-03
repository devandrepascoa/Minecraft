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
	Shader shader;
	Texture texture;
	std::vector<std::reference_wrapper<Mesh>> meshes;
	std::vector<std::reference_wrapper<Chunk>> chunks;
public:
	MasterRenderer();
	void addMesh(Mesh& mesh);
	void addChunk(Chunk& chunk);
	void clear();
	void render(const Camera& camera);
};
