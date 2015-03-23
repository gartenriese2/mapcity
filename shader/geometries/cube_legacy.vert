layout(std140) uniform ModelMatrixBuffer {
	mat4 ModelMatrix[NUM_MATRICES];
};

out vec3 color;
out vec3 n;
out vec3 worldpos;

uniform mat4 ViewProj;
uniform vec3 col;

void main() {

	vec4 pos = vec4((gl_VertexID>>0) & 0x01,
					(gl_VertexID>>1) & 0x01,
					(gl_VertexID>>2) & 0x01,
					0.0);
	pos = 1.0 - 2.0 * pos;

	vec3 normal = vec3(0.0);
	int nIndic = (gl_VertexID>>3);
	normal[nIndic] = pos[nIndic];

	worldpos = (ModelMatrix[gl_InstanceID] * pos).xyz;
	gl_Position = ViewProj * ModelMatrix[gl_InstanceID] * pos;
	color = col;
	n = normal;

}
