#version 450 core

layout(location = 0) out vec3 outNormal;
layout(location = 1) out vec4 outColor;
layout(location = 2) out vec3 outPosition;
layout(location = 3) out vec4 outLighting;

in vec4 color;
in vec3 n_w;
in vec3 n_vp;
in vec3 worldpos;
in vec3 l;

void main() {
	outNormal = n_w;
	outColor = color;
	outPosition = worldpos;
	const float cosTheta = clamp(dot(normalize(n_vp), normalize(l)), 0.0, 1.0);
	outLighting = color * cosTheta;
}
