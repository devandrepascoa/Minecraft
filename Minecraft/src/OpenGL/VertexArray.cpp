#include "VertexArray.h"
#include <glad/glad.h>
#include "../Utilities/Utils.h"

VertexArray::VertexArray(){
	GLCall(glGenVertexArrays(1, &rendererId));
	GLCall(glBindVertexArray(rendererId));
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &rendererId));
}

void VertexArray::bindBuffer(const VertexBuffer& vbo, const VertexBufferLayout& layout)
{
	this->bind();
	vbo.bind();
	auto items = layout.getItems();
	unsigned int offset = 0;
	for (size_t i = 0; i < items.size(); i++) {
		auto item = items[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, item.size, item.type, item.normalized, layout.getStride(), (void*)offset));
		offset += item.size * getSizeOfGLEnumType(item.type);
	}
}

void VertexArray::bind() const
{
	GLCall(glBindVertexArray(rendererId));
}

void VertexArray::unBind() const
{
	GLCall(glBindVertexArray(0));
}

unsigned int getSizeOfGLEnumType(GLenum type)
{
	switch (type) {
	case GL_FLOAT: return 4;
	case GL_UNSIGNED_INT: return 4;
	case GL_INT: return 4;
	}
	ASSERT(false);
	return 0;
}

