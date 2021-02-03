#include "IndexBuffer.h"
#include <glad/glad.h>
#include "../Utilities/Utils.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int size) :numIndices(size / sizeof(unsigned int))
{
	GLCall(glGenBuffers(1, &rendererId));
	this->updateData(data, size);
}

IndexBuffer::~IndexBuffer()
{
	GLCall(glDeleteBuffers(1, &rendererId));
}

void IndexBuffer::updateData(const unsigned int* data, unsigned int size)
{
	numIndices = size / sizeof(unsigned int);
	this->bind();
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
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
