#pragma once
#include "VertexBuffer.h"
#include <vector>
#include <glad/glad.h>
#include "../Utils.h"

struct VertexBufferElement {
	GLenum type;
	unsigned int size;
	bool normalized;
};

unsigned int getSizeOfGLEnumType(GLenum type);

class VertexBufferLayout {
private:
	std::vector<VertexBufferElement> items;
	unsigned int stride;
public:
	VertexBufferLayout() :stride(0) {}
	template<typename T>
	void push(unsigned int size) {
		static_assert(false);
	}

	template<>
	void push<float>(unsigned int size) {
		items.push_back({ GL_FLOAT, size,false });

		stride += size * getSizeOfGLEnumType(GL_FLOAT);
	}

	template<>
	void push<unsigned int>(unsigned int size) {
		items.push_back({ GL_UNSIGNED_INT, size,false });
		stride += size * getSizeOfGLEnumType(GL_UNSIGNED_INT);
	}

	template<>
	void push<int>(unsigned int size) {
		items.push_back({ GL_INT, size,false });
		stride += size * getSizeOfGLEnumType(GL_INT);
	}

	std::vector<VertexBufferElement> getItems() const { return items; };
	unsigned int getStride() const { return stride; };
};

class VertexArray {
private:
	unsigned int rendererId;
public:
	VertexArray();
	~VertexArray();

	void bindBuffer(const VertexBuffer& vbo, const VertexBufferLayout& layout);
	void bind() const;
	void unBind() const;
};