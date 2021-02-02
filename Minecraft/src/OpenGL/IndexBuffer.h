#pragma once

class IndexBuffer {
private:
	unsigned int rendererId;
	unsigned int numIndices;
public:
	IndexBuffer() = delete;
	IndexBuffer(const void* data, unsigned int size);
	~IndexBuffer();
	void bind() const;
	void unBind() const;
	unsigned int getNumIndices()const;
};