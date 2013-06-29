#version 410

uniform sampler2D tex;

in vec2 texCoord;
out vec3 color;

void main() {
	color = texture(tex, texCoord).xyz;
	color = vec3(texCoord,0);
}