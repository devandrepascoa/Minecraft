#include "IndexBuffer.h"
#include <glad/glad.h>
#include "../Utils.h"

IndexBuffer::IndexBuffer(const void* data, unsigned int size) :numIndices(size / sizeof(unsigned int))
{
	GLCall(glGenBuffers(1, &rendererId));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererId));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
	GLCall(glDeleteBuffers(1, &rendererId));
}


void IndexBuffer::bind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererId));
}

void IndexBuffer::unBind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

unsigned int IndexBuffer::getNumIndices() const
{
	return numIndices;
}
