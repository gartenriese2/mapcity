#version 450 core

layout(location = 0) out vec4 outColor;

in vec3 color;
in vec3 n;

void main() {
	outColor = vec4(color, 1.f);
}
