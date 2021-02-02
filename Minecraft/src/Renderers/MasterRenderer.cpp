#include "MasterRenderer.h"


void MasterRenderer::addCube(const Cube& cube)
{
	cubeRenderer.addCube(cube);
}

void MasterRenderer::render(const Camera& camera)
{
	cubeRenderer.render(camera);
}
