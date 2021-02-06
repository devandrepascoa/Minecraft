#include "Mesh.h"

Mesh::Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices) :ibo(&indices.front(), sizeof(unsigned int)* indices.size()),
vbo(&vertices.front(), sizeof(float)* vertices.size()), indices(indices), vertices(vertices) {
	VertexBufferLayout layout;
	layout.push<float>(3);
	layout.push<float>(2);
	layout.push<float>(1);
	vao.bindBuffer(vbo, layout);
}
Mesh::Mesh() : vbo({}, 0), ibo({}, 0) {
	VertexBufferLayout layout;
	layout.push<float>(3);
	layout.push<float>(2);
	layout.push<float>(1);
	vao.bindBuffer(vbo, layout);
}

void Mesh::updateData(std::vector<float> vertices, std::vector<unsigned int> indices)
{
	this->vertices = vertices;
	this->indices = indices;
}

void Mesh::updateBuffers()
{
	if (indices.empty() || vertices.empty())return;
	this->ibo.updateData(&indices.front(), sizeof(unsigned int) * indices.size());
	this->vbo.updateData(&vertices.front(), sizeof(float) * vertices.size());
}

VertexArray& Mesh::getVao()
{
	return vao;
}

VertexBuffer& Mesh::getVbo()
{
	return vbo;
}

IndexBuffer& Mesh::getIbo()
{
	return ibo;
}

std::vector<float>& Mesh::getVertices()
{
	return vertices;
}

std::vector<unsigned int>& Mesh::getIndices()
{
	return indices;
}

void Mesh::clearIndices()
{
	indices.clear();
}

void Mesh::clearVertices()
{
	vertices.clear();
}


