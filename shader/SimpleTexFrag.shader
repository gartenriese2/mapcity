#version 410

uniform sampler2D texColor;
uniform sampler2D texNormal;
uniform sampler2D texDepth;
uniform sampler2D texShadow;

uniform mat4 ProjMat;

in vec2 texCoord;
out vec3 color;

const int spiralSize = 9;
ivec2 spiral[spiralSize];

const int width = 1024;
const int height = 1024;
const float near = 0.1;
const float far = 10000.0;
const float fov = 45.0;
#define pix (height / (2.0 * tan(fov/2.0)))
const int turns = 7;
const float epsilon = 0.01;
const float worldSpaceRadius = 20;
const float bias = 0.5;
const float k = 1.0;

float getHierarchicalDepth(float d) {

	return -(near * far) / (d * (near - far) + far);

}

vec3 getViewSpaceFromScreenSpace(float z, int x, int y) {

	float xC = (1 - ProjMat[0][2]) / ProjMat[0][0] - 2 * (x + 0.5) / (width * ProjMat[0][0]);
	float yC = (1 + ProjMat[1][2]) / ProjMat[1][1] - 2 * (y + 0.5) / (height * ProjMat[1][1]);
	return vec3(vec2(xC,yC) * z, z);

}

void generateSpiral() {

	
	float screenSpaceRadius = -worldSpaceRadius * pix / getHierarchicalDepth(texture(texDepth, texCoord).x);

	float randomAngle = 30 * int(gl_FragCoord.x) ^ int(gl_FragCoord.y + 10 * gl_FragCoord.x * gl_FragCoord.y);

	for (int i = 0; i < spiralSize; i++) {

		float alpha = (i + 0.5) / spiralSize;
		float h = screenSpaceRadius * alpha;
		float angle = 2 * 3.14 * alpha * turns + randomAngle;
		vec2 u = vec2(cos(angle), sin(angle));
		spiral[i] = ivec2(gl_FragCoord.xy) + ivec2(h * u);

	}

}

vec3 sampleAO() {

	vec3 C = getViewSpaceFromScreenSpace(getHierarchicalDepth(texture(texDepth, texCoord).x), int(gl_FragCoord.x), int(gl_FragCoord.y));
	vec3 normal = texture(texNormal, texCoord).xyz;


	float a = 0.0;
	for (int i = 0; i < spiralSize; i++) {
		
		vec3 Q = getViewSpaceFromScreenSpace(getHierarchicalDepth(texture(texDepth, spiral[i] / 1024.0).x), spiral[i].x, spiral[i].y); 

    	vec3 v = Q - C;

    	float vv = dot(v, v);
    	float vn = dot(v, normal);

    	// D
    	// a += 2.0 * float(vv < worldSpaceRadius * worldSpaceRadius) * max(vn - bias, 0.0);

    	// B
    	float f = max(worldSpaceRadius * worldSpaceRadius - vv, 0.0); a += f * f * f * max((vn - bias) / (epsilon + vv), 0.0);

	}

	float intensityDivR6 = 1.0 / pow(worldSpaceRadius, 6);
	float A = pow(max(0.0, 1.0 - a * intensityDivR6 * (5.0 / spiralSize)), k);
	return vec3(A,A,A);

}

void main() {
	
	//generateSpiral();
	
	// color = texture(texShadow, texCoord).xyz;
	color = texture(texColor, texCoord).xyz;
	//color = sampleAO() * color;
	
}