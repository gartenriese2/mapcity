layout(std140) uniform ModelMatrixBuffer {
	mat4 ModelMatrix[NUM_MATRICES];
};
layout(std140) uniform ColorBuffer {
	vec4 Color[NUM_MATRICES];
};
layout(std140) uniform MiscBuffer {
	vec4 Misc[NUM_MATRICES]; // x = upper scale
};

out vec4 color;
out vec3 n_w;
out vec3 n_vp;
out vec3 worldpos;
out vec3 l;

uniform mat4 ViewProj;
uniform mat4 View;
uniform vec3 lightDir;

void main() {

	vec4 pos = vec4((gl_VertexID>>0) & 0x01,
					(gl_VertexID>>1) & 0x01,
					0.0,
					1.0);
	pos.xy = 1.0 - 2.0 * pos.xy;
	if (pos.xy == vec2(-1.0, 1.0)) {
		pos.x *= Misc[gl_InstanceID].x;
	} else if (pos.xy == vec2(1.0, 1.0)) {
		pos.x *= Misc[gl_InstanceID].y;
	}

	vec3 normal = vec3(0.0, 0.0, 1.0);

	worldpos = (ModelMatrix[gl_InstanceID] * pos).xyz;
	gl_Position = ViewProj * ModelMatrix[gl_InstanceID] * pos;
	color = Color[gl_InstanceID];
	n_w = normal;
	mat4 NormalMatrix = transpose(inverse(View * ModelMatrix[gl_InstanceID]));
	n_vp = (normalize(NormalMatrix * vec4(normal, 0.0))).xyz;

	l = (ViewProj * vec4(lightDir, 1.0)).xyz;
}
