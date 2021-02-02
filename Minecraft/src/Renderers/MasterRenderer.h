#pragma once
#include "CubeRenderer.h"
#include "../Camera.h"

class MasterRenderer {
private:
	CubeRenderer cubeRenderer;
public:
	void addCube(const Cube& cube);
	void render(const Camera&camera);
};
