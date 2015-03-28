#version 450 core

layout(std430, binding = 0) restrict readonly buffer ModelMatrixBuffer {
	mat4 ModelMatrix[];
};

in int gl_InstanceID;
in int gl_VertexID;

out vec3 color;
out vec3 n_w;
out vec3 n_vp;
out vec3 worldpos;
out vec3 l;

uniform mat4 ViewProj;
uniform mat4 View;
uniform vec3 col;
uniform vec3 lightDir;

void main() {

	vec4 pos = vec4((gl_VertexID>>0) & 0x01,
					(gl_VertexID>>1) & 0x01,
					(gl_VertexID>>2) & 0x01,
					0.0);
	pos = 1.0 - 2.0 * pos;

	vec3 normal = vec3(0.0);
	const int nIndic = (gl_VertexID>>3);
	normal[nIndic] = pos[nIndic];

	worldpos = (ModelMatrix[gl_InstanceID] * pos).xyz;
	gl_Position = ViewProj * ModelMatrix[gl_InstanceID] * pos;
	color = col;
	n_w = normal;
	const mat4 NormalMatrix = transpose(inverse(View * ModelMatrix[gl_InstanceID]));
	n_vp = (normalize(NormalMatrix * vec4(normal, 0.0))).xyz;

	l = (ViewProj * vec4(lightDir, 1.0)).xyz;
}
