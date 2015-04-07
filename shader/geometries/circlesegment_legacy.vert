layout(std140) uniform ModelMatrixBuffer {
	mat4 ModelMatrix[NUM_MATRICES];
};
layout(std140) uniform ColorBuffer {
	vec4 Color[NUM_MATRICES];
};
layout(std140) uniform MiscBuffer {
	vec4 Misc[NUM_MATRICES]; // x = degrees, y = innerradius
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

	float deg = clamp(Misc[gl_InstanceID].x, 0.01, 360.0);
	float innerradius = clamp(Misc[gl_InstanceID].y, 0.01, 0.99);
	float rad = radians(float(gl_VertexID / 2) * deg * 0.01); // 0.01 == 1/numSegments
	vec4 pos = vec4(0.0, 0.0, 0.0, 1.0);
	if (gl_VertexID % 2 == 0) {
		pos.x = innerradius * cos(rad);
		pos.y = innerradius * sin(rad);
	} else {
		pos.x = cos(rad);
		pos.y = sin(rad);
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
