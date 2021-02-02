#shader vertex
#version 330 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoords;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main() {
	gl_Position = projection*view*model*position;
}

#shader fragment
#version 330 core
out vec4 FragColor;

void main() {
	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}
