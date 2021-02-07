#include "Chunk.h"
#include <glm/vec2.hpp>
#include <iostream>
#include <glm/gtc/noise.hpp>
#include <glm/vec4.hpp>
#include "ChunkManager.h"

Chunk::Chunk() :buffered(false), meshed(false) {}

Chunk::Chunk(glm::vec3 position) : Entity(position), buffered(false), meshed(false)
{
}

void Chunk::addFaceToMesh(const glm::vec3& position, FaceType faceType, Block* block) {
	const std::array<float, 12>& faceVertices = getFaceVertices(faceType);
	const std::array<float, 8>& texCoords = getFaceTexCoords(faceType, block->getType());

	float light = 0.0f;
	switch (faceType) {
	case FaceType::TOP:
		light = 1.0f;
		break;
	case FaceType::BOTTOM:
		light = 0.4f;
		break;
	case FaceType::RIGHT:
	case FaceType::LEFT:
		light = 0.8f;
		break;
	case FaceType::FRONT:
	case FaceType::BACK:
		light = 0.6f;
		break;
	}
	if (block->getFocus())
		light *= 2.0f;

	std::vector<float>& vertices = mesh.getVertices();
	std::vector<unsigned int>& indices = mesh.getIndices();
	int numVertices = vertices.size() / 6;
	for (size_t i = 0, k = 0; i < 12; i += 3, k += 2) {
		vertices.push_back((float)position.x + faceVertices[i]);
		vertices.push_back((float)position.y + faceVertices[i + 1]);
		vertices.push_back((float)position.z + faceVertices[i + 2]);
		vertices.push_back(texCoords[k]);
		vertices.push_back(texCoords[k + 1]);
		vertices.push_back(light);
	}

	indices.push_back(numVertices);
	indices.push_back(numVertices + 1);
	indices.push_back(numVertices + 2);
	indices.push_back(numVertices + 2);
	indices.push_back(numVertices + 3);
	indices.push_back(numVertices);
}

void Chunk::generateChunk()
{
	for (size_t i = 0; i < 16; i++) {
		for (size_t k = 0; k < 16; k++) {
			int x = i + position.x * 16;
			int y = k + position.z * 16;
			double val = glm::simplex(glm::vec2(x / 128.f, y / 128.f));
			double val2 = glm::simplex(glm::vec2(x / 32.f, y / 32.f));
			double val3 = glm::simplex(glm::vec2(x / 16.f, y / 16.f));
			val *= val2;
			val *= val3;

			val = (val + 1) / 2;
			val *= 64;
			val += 60;

			for (size_t j = 0; j < 256; j++) {
				if (j > val)
					blocks[i][j][k] = Block(toWorldPosition(glm::vec3(i, j, k)), BlockType::AIR);
				else {
					if (j > 80)
						blocks[i][j][k] = Block(toWorldPosition(glm::vec3(i, j, k)), BlockType::DIRT);
					else
						blocks[i][j][k] = Block(toWorldPosition(glm::vec3(i, j, k)), BlockType::STONE);
				}
			}
		}
	}

}

void Chunk::generateMesh(const ChunkManager& manager)
{

	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 256; j++) {
			for (int k = 0; k < 16; k++) {
				Block* b = &blocks[i][j][k];
				if (b->getType() == BlockType::AIR) continue;

				Block* block = getBlock(manager, glm::vec3(i, j + 1, k));
				if (block != nullptr && block->getType() == BlockType::AIR)
					addFaceToMesh(glm::vec3(i, j, k), FaceType::TOP, b);

				block = getBlock(manager, glm::vec3(i, j - 1, k));
				if (block != nullptr && block->getType() == BlockType::AIR)
					addFaceToMesh(glm::vec3(i, j, k), FaceType::BOTTOM, b);

				block = getBlock(manager, glm::vec3(i + 1, j, k));
				if (block != nullptr && block->getType() == BlockType::AIR)
					addFaceToMesh(glm::vec3(i, j, k), FaceType::RIGHT, b);

				block = getBlock(manager, glm::vec3(i - 1, j, k));
				if (block != nullptr && block->getType() == BlockType::AIR)
					addFaceToMesh(glm::vec3(i, j, k), FaceType::LEFT, b);

				block = getBlock(manager, glm::vec3(i, j, k + 1));
				if (block != nullptr && block->getType() == BlockType::AIR)
					addFaceToMesh(glm::vec3(i, j, k), FaceType::FRONT, b);

				block = getBlock(manager, glm::vec3(i, j, k - 1));
				if (block != nullptr && block->getType() == BlockType::AIR)
					addFaceToMesh(glm::vec3(i, j, k), FaceType::BACK, b);
			}
		}
	}

}

Block(*Chunk::getBlocks())[16][256][16]
{
	return &blocks;
}

Block* Chunk::getBlock(const glm::vec3& position)
{
	if (isWithinBounds(position))
		return &blocks[(int)position.x][(int)position.y][(int)position.z];
	return nullptr;
}

Block* Chunk::getBlock(const ChunkManager& manager, const glm::vec3& position)
{
	if (isWithinBounds(position))
		return &blocks[(int)position.x][(int)position.y][(int)position.z];
	if (position.y < 0 || position.y > 255) return nullptr;
	return manager.getBlock(toWorldPosition(position));
}

bool Chunk::isWithinBounds(const glm::vec3& position)
{
	return position.x >= 0 && position.x < 16 &&
		position.y >= 0 && position.y < 256 &&
		position.z >= 0 && position.z < 16;
}

glm::vec3 Chunk::toWorldPosition(const glm::vec3& position)
{
	return (glm::vec3(this->position.x * 16, this->position.y * 256, this->position.z * 16)) + position;
}

glm::vec3 Chunk::toChunkPosition(const glm::vec3& position)
{
	return glm::vec3();
}

bool Chunk::isBuffered()
{
	return buffered;
}

bool Chunk::hasMesh()
{
	return meshed;
}

void Chunk::setMesh(bool meshed)
{
	this->meshed = meshed;
}

void Chunk::setBuffered(bool buffered)
{
	this->buffered = buffered;
}

Mesh& Chunk::getMesh()
{
	return mesh;
}
