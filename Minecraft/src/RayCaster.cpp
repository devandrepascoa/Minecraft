#include "RayCaster.h"
#include <iostream>
#include <glm/gtx/string_cast.hpp>

RayCaster::RayCaster(const Camera& camera) : camera(camera) {}


Block* RayCaster::getSelectedBlock(const ChunkManager& chunkManager)
{
	glm::vec3 rayStartPosition = camera.getPosition();
	glm::vec3 rayEndPosition = camera.getPosition();
	glm::vec3 ray = forwardsVector(camera.getRotation());
	float step = 0.05f;
	float cStep = step;
	while (glm::distance(rayStartPosition, rayEndPosition) < 10.0f) {
		rayEndPosition = rayStartPosition + ray * cStep;
		Block* block = chunkManager.getBlock(rayEndPosition);
		if (block != nullptr && block->getType() != BlockType::AIR) {
			return block;
		}
		cStep += step;
	}
	return nullptr;
}
