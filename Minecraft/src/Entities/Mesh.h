#pragma once
#include <vector>
#include "../OpenGL/VertexArray.h"
#include "../OpenGL/VertexBuffer.h"
#include "../OpenGL/IndexBuffer.h"
class Mesh
{
private:
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	VertexArray vao;
	VertexBuffer vbo;
	IndexBuffer ibo;
public:
	Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);
	Mesh();
	void updateData(std::vector<float> vertices, std::vector<unsigned int> indices);
	void updateBuffers();
	VertexArray& getVao();
	VertexBuffer& getVbo();
	IndexBuffer& getIbo();
	std::vector<float>& getVertices();
	std::vector<unsigned int>& getIndices();
	void clearIndices();
	void clearVertices();
};

