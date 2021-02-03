#shader vertex
#version 330 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec2 inTexCoord;
layout(location = 2) in float inLight;
out vec2 texCoord;
out float light;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main() {
	gl_Position = projection*view*model*position;
	texCoord = inTexCoord;
	light = inLight;
}

#shader fragment
#version 330 core
out vec4 FragColor;
in vec2 texCoord;
in float light;

uniform sampler2D ourTexture;

void main() {
	FragColor = texture(ourTexture, texCoord)*vec4(light,light,light,1.0f);
}
