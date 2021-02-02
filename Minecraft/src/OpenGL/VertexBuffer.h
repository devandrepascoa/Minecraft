#pragma once

class VertexBuffer {
private:
	unsigned int rendererId;
public:
	VertexBuffer() = delete;
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();
	void updateData(const void* data, unsigned int size);
	void bind() const;
	void unBind() const;
};