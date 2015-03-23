#version 450 core

layout(std430, binding = 0) restrict readonly buffer ModelMatrixBuffer {
	mat4 ModelMatrix[];
};

in int gl_InstanceID;
in int gl_VertexID;

out vec3 color;
out vec3 n;

uniform mat4 ViewProj;
uniform vec3 col;

void main() {

	vec4 pos = vec4((gl_VertexID>>0) & 0x01,
					(gl_VertexID>>1) & 0x01,
					0.0,
					0.0);
	pos = 1.0 - 2.0 * pos;

	vec3 normal = vec3(0.0, 0.0, 1.0);

	gl_Position = ViewProj * ModelMatrix[gl_InstanceID] * pos;
	color = col;
	n = normal;

}
