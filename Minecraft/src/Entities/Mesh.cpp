#include "Mesh.h"

Mesh::Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices) :vao(nullptr), ibo(nullptr), vbo(nullptr), vertices(vertices), indices(indices) {
}
Mesh::Mesh() : vao(nullptr), ibo(nullptr), vbo(nullptr) {
}

Mesh::~Mesh()
{
	delete ibo;
	delete vao;
	delete vbo;
}

void Mesh::updateData(std::vector<float> vertices, std::vector<unsigned int> indices)
{
	this->vertices = vertices;
	this->indices = indices;
}
void Mesh::createBuffers() {

	ibo = new IndexBuffer(&indices.front(), sizeof(unsigned int) * indices.size());
	vbo = new VertexBuffer(&vertices.front(), sizeof(float) * vertices.size());
	vao = new VertexArray();
	VertexBufferLayout layout;
	layout.push<float>(3);
	layout.push<float>(2);
	layout.push<float>(1);
	vao->bindBuffer(*vbo, layout);
}

bool Mesh::buffersExist()
{
	return vao != nullptr && vbo != nullptr && ibo != nullptr;
}

void Mesh::updateBuffers()
{
	if (indices.empty() || vertices.empty())return;
	if (!buffersExist())
		createBuffers();

	this->ibo->updateData(&indices.front(), sizeof(unsigned int) * indices.size());
	this->vbo->updateData(&vertices.front(), sizeof(float) * vertices.size());
	clearIndices();
	clearVertices();
}

VertexArray* Mesh::getVao()
{
	return vao;
}

VertexBuffer* Mesh::getVbo()
{
	return vbo;
}

IndexBuffer* Mesh::getIbo()
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


