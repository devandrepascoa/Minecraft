#pragma once
#include <glm/vec3.hpp>
#include "Entity.h"
#include <array>

static std::array<float, 20> frontFace = {
	-0.5f, -0.5f, -0.5f,1,0,
	0.5f, -0.5f, -0.5f,0,0,
	0.5f,  0.5f, -0.5f,0,1,
	-0.5f,  0.5f, -0.5f,1,1
};
static std::array<float, 20> backFace = {
	-0.5f, -0.5f,  0.5f,1,0,
	0.5f, -0.5f,  0.5f,0,0,
	0.5f,  0.5f,  0.5f,0,1,
	-0.5f,  0.5f,  0.5f,1,1
};
static std::array<float, 20> leftFace = {
	-0.5f,  0.5f,  0.5f,1,0,
	-0.5f,  0.5f, -0.5f,0,0,
	-0.5f, -0.5f, -0.5f,0,1,
	-0.5f, -0.5f,  0.5f,1,1
};
static std::array<float, 20> rightFace = {
	0.5f,  0.5f,  0.5f,1,0,
	0.5f,  0.5f, -0.5f,0,0,
	0.5f, -0.5f, -0.5f,0,1,
	0.5f, -0.5f,  0.5f,1,1
};
static std::array<float, 20> bottomFace = {
	-0.5f, -0.5f, -0.5f,1,0,
	0.5f, -0.5f, -0.5f,0,0,
	0.5f, -0.5f,  0.5f,0,1,
	-0.5f, -0.5f,  0.5f,1,1
};
static std::array<float, 20> topFace = {
	-0.5f,  0.5f, -0.5f,1,0,
	0.5f,  0.5f, -0.5f,0,0,
	0.5f,  0.5f,  0.5f,0,1,
	-0.5f,  0.5f,  0.5f,1,1
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


enum class FaceType { FRONT, BACK, LEFT, RIGHT, TOP, BOTTOM };

const static std::array<float, 20>& getFaceVertices(FaceType faceType) {
	switch (faceType) {
	case FaceType::FRONT: return frontFace;
	case FaceType::BACK: return backFace;
	case FaceType::LEFT: return leftFace;
	case FaceType::RIGHT: return rightFace;
	case FaceType::TOP: return topFace;
	case FaceType::BOTTOM: return bottomFace;
	}
}

class Cube : public Entity {
public:
	Cube(glm::vec3 position);
};
