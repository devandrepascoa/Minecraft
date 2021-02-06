#pragma once
#include "../Entities/Block.h"
#include "../Entities/Mesh.h"
#include <glm/vec2.hpp>

class ChunkManager;
class Chunk : public Entity
{
private:
	Block blocks[16][256][16];
	Mesh mesh;
public:
	Chunk();
	Chunk(glm::vec3 position);
	void generateChunk();
	void generateMesh(const ChunkManager& manager);
	Block(*getBlocks())[16][256][16];
	Block* getBlock(const glm::vec3& position);
	Block* getBlock(const ChunkManager& manager,const glm::vec3& position);
	static bool isWithinBounds(const glm::vec3& position);
	glm::vec3 toWorldPosition(const glm::vec3& position);
	glm::vec3 toChunkPosition(const glm::vec3& position);
	Mesh& getMesh() ;
};

