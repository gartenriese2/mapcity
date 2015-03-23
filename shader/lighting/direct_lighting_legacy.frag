#version 330 core

layout(location = 0) out vec4 outColor;

in vec3 color;
in vec3 n;

const vec3 lightDir = vec3(1.0, -2.0, 3.0);

void main() {
	vec3 l = normalize(lightDir);
	float cosTheta = clamp(dot(n, l), 0.0, 1.0);
	outColor = vec4(color * cosTheta, 1.0);
}
