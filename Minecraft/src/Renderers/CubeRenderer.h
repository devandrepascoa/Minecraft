#pragma once
#include <vector>
#include "../Entities/Cube.h"
#include "../Shader.h"
#include "../Camera.h"
#include "../Entities/Model.h"
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
