#shader vertex
#version 330 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec2 inTexCoord;

out vec2 texCoord;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main() {
	gl_Position = projection*view*model*position;
	texCoord = inTexCoord;
}

#shader fragment
#version 330 core
out vec4 FragColor;
in vec2 texCoord;

uniform sampler2D ourTexture;

void main() {
	FragColor = texture(ourTexture, texCoord);
}
