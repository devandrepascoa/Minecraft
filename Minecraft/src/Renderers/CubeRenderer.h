#pragma once
#include <vector>
#include "../Entities/Cube.h"
#include "../Shader.h"
#include "../Camera.h"
#include "../Entities/Model.h"

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



class CubeRenderer {
private:
	Shader shader;
	Model cubeModel;
	std::vector<Cube>cubes;
public:
	CubeRenderer();
	void addCube(const Cube& cube);
	void render(const Camera& camera);
};
