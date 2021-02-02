#include "Utils.h"
#include <iostream>

void GLClearError() {
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line) {
	while (GLenum error = glGetError()) {
		std::cout << "Opengl Error (" << "0x" << std::hex << error << "): " << function << " " << file << ":" << line << std::endl;
		return false;
	}
	return true;
}

