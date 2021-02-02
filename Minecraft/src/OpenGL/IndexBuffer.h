#pragma once

class IndexBuffer {
private:
	unsigned int rendererId;
	unsigned int numIndices;
public:
	IndexBuffer() = delete;
	IndexBuffer(const unsigned int* data, unsigned int size);
	~IndexBuffer();
	void updateData(const unsigned int* data, unsigned int size);
	void bind() const;
	void unBind() const;
	unsigned int getNumIndices()const;
};