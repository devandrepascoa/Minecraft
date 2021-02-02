#pragma once
#include "../OpenGL/VertexArray.h"
#include "../OpenGL/IndexBuffer.h"

class Model {
private:
	VertexArray vao;
	VertexBuffer vbo;
	IndexBuffer ibo;
public:
	Model() = delete;
	Model(const void* vertices, const unsigned int* indices, unsigned int numVertices, unsigned int numIndices);
	Model(const std::vector<float>& vertices,const std::vector<unsigned int>& indices);
	VertexArray& getVao();
	VertexBuffer& getVbo();
	IndexBuffer& getIbo();
};
