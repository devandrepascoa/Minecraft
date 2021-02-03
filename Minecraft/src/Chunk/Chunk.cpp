#include "Chunk.h"
#include <glm/vec2.hpp>
#include <iostream>
#include <glm/gtc/noise.hpp>
#include <glm/vec4.hpp>
Chunk::Chunk() {}

Chunk::Chunk(glm::vec3 position) :Entity(position)
{
}

void addFaceToMesh(Mesh& mesh, glm::vec3 position, FaceType faceType, BlockType type) {
	const std::array<float, 12>& faceVertices = getFaceVertices(faceType);
	const std::array<float, 8>& texCoords = getFaceTexCoords(faceType, type);

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
					blocks[i][j][k] = Block(BlockType::AIR);
				else {
					if (j > 80)
						blocks[i][j][k] = Block(BlockType::DIRT);
					else
						blocks[i][j][k] = Block(BlockType::STONE);
				}
			}
		}
	}

}

void Chunk::generateMesh()
{
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 256; j++) {
			for (int k = 0; k < 16; k++) {
				Block b = blocks[i][j][k];
				if (b.getType() == BlockType::AIR) continue;

				if (j == 255 || j < 255 && blocks[i][j + 1][k].getType() == BlockType::AIR)
					addFaceToMesh(mesh, glm::vec3(i, j, k), FaceType::TOP, b.getType());
				if (j == 0 || j > 0 && blocks[i][j - 1][k].getType() == BlockType::AIR)
					addFaceToMesh(mesh, glm::vec3(i, j, k), FaceType::BOTTOM, b.getType());
				if (i == 15 || i < 15 && blocks[i + 1][j][k].getType() == BlockType::AIR)
					addFaceToMesh(mesh, glm::vec3(i, j, k), FaceType::RIGHT, b.getType());
				if (i == 0 || i > 0 && blocks[i - 1][j][k].getType() == BlockType::AIR)
					addFaceToMesh(mesh, glm::vec3(i, j, k), FaceType::LEFT, b.getType());
				if (k == 15 || k < 15 && blocks[i][j][k + 1].getType() == BlockType::AIR)
					addFaceToMesh(mesh, glm::vec3(i, j, k), FaceType::BACK, b.getType());
				if (k == 0 || k > 0 && blocks[i][j][k - 1].getType() == BlockType::AIR)
					addFaceToMesh(mesh, glm::vec3(i, j, k), FaceType::FRONT, b.getType());
			}
		}
	}

	mesh.updateBuffers();

}

Block(&Chunk::getBlocks())[16][256][16]
{
	return blocks;
}

Mesh& Chunk::getMesh()
{
	return mesh;
}
