#version 450 core

layout(std430, binding = 0) restrict readonly buffer ModelMatrixBuffer {
	mat4 ModelMatrix[];
};
layout(std430, binding = 1) restrict readonly buffer ColorBuffer {
	vec4 Color[];
};
layout(std430, binding = 2) restrict readonly buffer MiscBuffer {
	vec4 Misc[]; // x = degrees, y = innerradius right, z = innerradius left, w = outerradius left
};

in int gl_InstanceID;
in int gl_VertexID;

out vec4 color;
out vec3 n_w;
out vec3 n_vp;
out vec3 worldpos;
out vec3 l;

uniform mat4 ViewProj;
uniform mat4 View;
uniform vec3 lightDir;

void main() {

	const float deg = clamp(Misc[gl_InstanceID].x, 0.01, 360.0);
	const float innerradiusRight = max(Misc[gl_InstanceID].y, 0.01);
	const float innerradiusLeft = max(Misc[gl_InstanceID].z, 0.01);
	const float outerradiusLeft = max(Misc[gl_InstanceID].w, innerradiusLeft + 0.01);
	const float rel = float(gl_VertexID / 2) * 0.01; // 0.01 == 1/numSegments
	const float rad = radians(rel * deg);
	const float inRad = (1.0 - rel) * innerradiusRight + rel * innerradiusLeft;
	const float outRad = 1.0 + rel * (outerradiusLeft - 1.0);
	vec4 pos = vec4(0.0, 0.0, 0.0, 1.0);
	if (gl_VertexID % 2 == 0) {
		pos.x = inRad * cos(rad);
		pos.y = inRad * sin(rad);
	} else {
		pos.x = outRad * cos(rad);
		pos.y = outRad * sin(rad);
	}

	vec3 normal = vec3(0.0, 0.0, 1.0);

	worldpos = (ModelMatrix[gl_InstanceID] * pos).xyz;
	gl_Position = ViewProj * ModelMatrix[gl_InstanceID] * pos;
	color = Color[gl_InstanceID];
	n_w = normal;
	const mat4 NormalMatrix = transpose(inverse(View * ModelMatrix[gl_InstanceID]));
	n_vp = (normalize(NormalMatrix * vec4(normal, 0.0))).xyz;

	l = (ViewProj * vec4(lightDir, 1.0)).xyz;
}
