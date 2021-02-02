#pragma once
#include "CubeRenderer.h"
#include "../Camera.h"
#include "../Entities/Mesh.h"
#include "../Texture.h"

class MasterRenderer {
private:
	CubeRenderer cubeRenderer;
	Shader shader;
	Texture texture;
	std::vector<std::reference_wrapper<Mesh>> meshes;
public:
	MasterRenderer();
	void addCube(const Cube& cube);
	void addMesh(Mesh& mesh);

	void render(const Camera& camera);
};
