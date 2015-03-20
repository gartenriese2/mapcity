#version 450 core

layout(std430, binding = 0) restrict readonly buffer ModelMatrixBuffer {
	mat4 ModelMatrix[];
};

in int gl_InstanceID;
in int gl_VertexID;

out vec3 color;

uniform mat4 ViewProj;
uniform vec3 col;

void main() {

	vec4 pos = vec4((gl_VertexID>>0) & 0x01,
					(gl_VertexID>>1) & 0x01,
					0.0,
					0.0);
	pos = 1.0 - 2.0 * pos;
	// 00 -> (1, 1, 0)
	// 01 -> (-1, 1, 0)
	// 10 -> (1, -1, 0)
	// 11 -> (-1, -1, 0)

	vec3 normal = vec3(0.0, 0.0, 1.0);

	gl_Position = ViewProj * ModelMatrix[gl_InstanceID] * pos;
	color = col;

}
