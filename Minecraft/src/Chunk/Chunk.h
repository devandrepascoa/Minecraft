#pragma once
#include "../Entities/Block.h"
#include "../Entities/Mesh.h"
class Chunk : public Entity
{
private:
	Block blocks[16][256][16];
	Mesh mesh;
public:
	Chunk();
	Chunk(glm::vec3 position);
	void generateChunk();
	void generateMesh();
	Block(&getBlocks())[16][256][16];
	Mesh& getMesh() ;
};

