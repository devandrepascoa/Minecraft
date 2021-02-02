#include "VertexBuffer.h"
#include <glad/glad.h>
#include "../Utils.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	GLCall(glGenBuffers(1, &rendererId));
	this->updateData(data, size);
}


VertexBuffer::~VertexBuffer()
{
	GLCall(glDeleteBuffers(1, &rendererId));
}

void VertexBuffer::updateData(const void* data, unsigned int size)
{
	this->bind();
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}


void VertexBuffer::bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, rendererId));
}

void VertexBuffer::unBind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
