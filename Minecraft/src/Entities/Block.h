#pragma once
#include <glm/vec3.hpp>
#include "Entity.h"
#include <array>
#include <map>
#include "../Utilities/Utils.h"

enum class FaceType { FRONT, BACK, LEFT, RIGHT, TOP, BOTTOM };

enum class BlockType { AIR, DIRT, STONE, GRASS };

static std::array<float, 12> frontFace = {

	0.5f, 0.5f, 0.5f,
	-0.5f, 0.5f, 0.5f,
	-0.5f,  -0.5f, 0.5f,
	0.5f,  -0.5f, 0.5f,
};

static std::array<float, 12> backFace = {
	-0.5f, 0.5f,  -0.5f,
	0.5f, 0.5f,  -0.5f,
	0.5f,  -0.5f,  -0.5f,
	-0.5f,  -0.5f,  -0.5f
};

static std::array<float, 12> leftFace = {
	-0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f,  0.5f,
};

static std::array<float, 12> rightFace = {
	0.5f,  0.5f,  -0.5f,
	0.5f,  0.5f, 0.5f,
	0.5f, -0.5f, 0.5f,
	0.5f, -0.5f,  -0.5f,
};

static std::array<float, 12> bottomFace = {
	-0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f, -0.5f,  0.5f,
	-0.5f, -0.5f,  0.5f
};

static std::array<float, 12> topFace = {
	0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f,  0.5f,
	0.5f,  0.5f,  0.5f,
};

static std::array<float, 8> getAtlasTexCoords(int x, int y, int w = 16, int h = 16) {
	float xPos = ((float)x) / w;
	float yPos = ((float)y) / h;

	return {
				xPos + 1.0f / w, yPos,
				xPos , yPos ,
				xPos , yPos + 1.0f / h,
				xPos + 1.0f / w, yPos + 1.0f / h,
	};
};
// 1 0 bottom-right corner
// 0 0 bottom-left corner
// 0 1 top-left corner
// 1 1 top-right corner
static std::map<FaceType, std::array<float, 8>> dirtTexCoords = {
	{FaceType::FRONT,getAtlasTexCoords(2,15)},
	{FaceType::BACK,getAtlasTexCoords(2,15)},
	{FaceType::LEFT,getAtlasTexCoords(2,15)},
	{FaceType::RIGHT,getAtlasTexCoords(2,15)},
	{FaceType::TOP,getAtlasTexCoords(2,15)},
	{FaceType::BOTTOM,getAtlasTexCoords(2,15)},
};
static std::map<FaceType, std::array<float, 8>> grassTexCoords = {
	{FaceType::FRONT,getAtlasTexCoords(3,15)},
	{FaceType::BACK,getAtlasTexCoords(3,15)},
	{FaceType::LEFT,getAtlasTexCoords(3,15)},
	{FaceType::RIGHT,getAtlasTexCoords(3,15)},
	{FaceType::TOP,getAtlasTexCoords(1,6)},
	{FaceType::BOTTOM,getAtlasTexCoords(2,15)},
};
static std::map<FaceType, std::array<float, 8>> stoneTexCoords = {
	{FaceType::FRONT,getAtlasTexCoords(1,15)},
	{FaceType::BACK,getAtlasTexCoords(1,15)},
	{FaceType::LEFT,getAtlasTexCoords(1,15)},
	{FaceType::RIGHT,getAtlasTexCoords(1,15)},
	{FaceType::TOP,getAtlasTexCoords(1,15)},
	{FaceType::BOTTOM,getAtlasTexCoords(1,15)},
};


static float vertices[] = {
	 -0.5f,0.5f,-0.5f, 0,0,
	 -0.5f,-0.5f,-0.5f,0,1,
	 0.5f,-0.5f,-0.5f,1,1,
	 0.5f,0.5f,-0.5f,1,0,

	 -0.5f,0.5f,0.5f,0,0,
	 -0.5f,-0.5f,0.5f,0,1,
	 0.5f,-0.5f,0.5f,1,1,
	 0.5f,0.5f,0.5f,1,0,

	 0.5f,0.5f,-0.5f,0,0,
	 0.5f,-0.5f,-0.5f,0,1,
	 0.5f,-0.5f,0.5f,1,1,
	 0.5f,0.5f,0.5f,1,0,

	 -0.5f,0.5f,-0.5f,0,0,
	 -0.5f,-0.5f,-0.5f,0,1,
	 -0.5f,-0.5f,0.5f,1,1,
	 -0.5f,0.5f,0.5f,1,0,

	 -0.5f,0.5f,0.5f,0,0,
	 -0.5f,0.5f,-0.5f,0,1,
	 0.5f,0.5f,-0.5f,1,1,
	 0.5f,0.5f,0.5f,1,0,

	 -0.5f,-0.5f,0.5f,0,0,
	 -0.5f,-0.5f,-0.5f,0,1,
	 0.5f,-0.5f,-0.5f,1,1,
	 0.5f,-0.5f,0.5f,1,0
};

static unsigned int indices[] = {
	  0,1,3,
	  3,1,2,
	  4,5,7,
	  7,5,6,
	  8,9,11,
	  11,9,10,
	  12,13,15,
	  15,13,14,
	  16,17,19,
	  19,17,18,
	  20,21,23,
	  23,21,22
};

static float triangleVertices[] = {
	 0.5f,  0.5f, 0.0f,0,0,  // top right
	 0.5f, -0.5f, 0.0f,0,0,  // bottom right
	-0.5f, -0.5f, 0.0f,0,0,  // bottom left
	-0.5f,  0.5f, 0.0f,0,0,   // top left 
};
static unsigned int triangleIndices[] = {  // note that we start from 0!
	0, 1, 3,   // first triangle
	1, 2, 3    // second triangle
};



const static std::array<float, 12>& getFaceVertices(FaceType faceType) {
	switch (faceType) {
	case FaceType::FRONT: return frontFace;
	case FaceType::BACK: return backFace;
	case FaceType::LEFT: return leftFace;
	case FaceType::RIGHT: return rightFace;
	case FaceType::TOP: return topFace;
	case FaceType::BOTTOM: return bottomFace;
	}
	ASSERT(false);
	return {};
}

const static std::array<float, 8>& getFaceTexCoords(FaceType faceType, BlockType type) {
	switch (type) {
	case BlockType::DIRT: return dirtTexCoords[faceType];
	case BlockType::GRASS: return grassTexCoords[faceType];
	case BlockType::STONE: return stoneTexCoords[faceType];
	}
	ASSERT(false);
	return {};
}




class Block : public Entity {
private:
	BlockType type;
	bool focus;
public:
	Block();
	Block(glm::vec3 position, BlockType type);
	BlockType getType() const;
	bool getFocus() const;
	void setFocus(bool focus);
	void setType(BlockType type);
};
