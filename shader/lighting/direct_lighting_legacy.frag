#version 330 core

layout(location = 0) out vec4 outNormal;
layout(location = 1) out vec4 outColor;
layout(location = 2) out vec4 outPosition;
layout(location = 3) out vec4 outLighting;

in vec4 color;
in vec3 n_w;
in vec3 n_vp;
in vec3 worldpos;
in vec3 l;

void main() {
	outNormal = vec4(n_w, 0.0);
	outColor = color;
	outPosition = vec4(worldpos, 1.0);
	float cosTheta = clamp(dot(normalize(n_vp), normalize(l)), 0.0, 1.0);
	outLighting = color * cosTheta;
}
