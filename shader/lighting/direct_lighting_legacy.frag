#version 330 core

layout(location = 0) out vec4 outNormal;
layout(location = 1) out vec4 outColor;
layout(location = 2) out vec4 outPosition;
layout(location = 3) out vec4 outLighting;

in vec3 color;
in vec3 n;
in vec3 worldpos;

const vec3 lightDir = vec3(1.0, -2.0, 3.0);

void main() {
	outNormal = vec4(n, 0.0);
	outColor = vec4(color, 1.0);
	outPosition = vec4(worldpos, 1.0);
	vec3 l = normalize(lightDir);
	float cosTheta = clamp(dot(n, l), 0.0, 1.0);
	outLighting = vec4(color * cosTheta, 1.0);
}
