#include "Texture.h"
#include "Utils.h"
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "../vendor/stb/stb_image.h"

Texture::Texture(std::string path) {
	type = GL_TEXTURE_2D;
	GLCall(glGenTextures(1, &texture_ID));
	GLCall(glBindTexture(GL_TEXTURE_2D, texture_ID));
	// set the texture wrapping/filtering options (on the currently bound texture object)
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
	// load and generate the texture
	stbi_set_flip_vertically_on_load(true);
	int width, height, n_channels;
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &n_channels, 4);
	if (data)
	{
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));
		GLCall(glGenerateMipmap(GL_TEXTURE_2D));
	}
	else
	{
		std::cerr << "Failed to load texture" << std::endl;
		ASSERT(false);
	}
	stbi_image_free(data);
}

Texture::~Texture() {
	GLCall(glDeleteTextures(type, &texture_ID));
}

void Texture::Bind(unsigned int slot) const {
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(type, texture_ID));
}

void Texture::UnBind() const {
	GLCall(glBindTexture(type, 0));
}
