#pragma once
#include <glm/vec3.hpp>
#include "Chunk/ChunkManager.h"
class RayCaster
{
private:
	const Camera& camera;
	glm::vec3 getRay();
public:
	RayCaster(const Camera& camera);
	Block* getSelectedBlock(const ChunkManager& chunkManager);
};

