#pragma once
#include <glad/glad.h>
#include <cstddef>
#include <string>
#include <vector>

class Texture
{
public:
	unsigned int texture_ID;
	GLenum type;

	Texture(std::string path);
	~Texture();

	void Bind(unsigned int slot) const;

	void UnBind() const;
};