#include "Model.h"

Model::Model(const void* vertices, const unsigned int* indices, unsigned int sizeVertices, unsigned int sizeIndices) :ibo(indices, sizeIndices), vbo(vertices, sizeVertices) {

	VertexBufferLayout layout;
	layout.push<float>(3);
	layout.push<unsigned int>(2);
	vao.bindBuffer(vbo, layout);
}

Model::Model(const std::vector<float>& vertices,const std::vector<unsigned int>& indices) :ibo(&indices.front(), sizeof(unsigned int)* indices.size()), vbo(&vertices.front(), sizeof(float)* vertices.size()) {

	VertexBufferLayout layout;
	layout.push<float>(3);
	layout.push<unsigned int>(2);
	vao.bindBuffer(vbo, layout);
}

VertexArray& Model::getVao()
{
	return vao;
}

VertexBuffer& Model::getVbo()
{
	return vbo;
}

IndexBuffer& Model::getIbo()
{
	return ibo;
}
