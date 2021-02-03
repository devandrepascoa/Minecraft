#pragma once
#include "../OpenGL/Shader.h"
#include "../OpenGL/Texture.h"
#include "../Camera.h"
#include "../Chunk/Chunk.h"

class ChunkRenderer
{
private:
	Shader shader;
	Texture textureAtlas;
public:
	ChunkRenderer();
	void render(const Camera& camera, Chunk& chunk);
};

