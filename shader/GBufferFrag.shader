#version 410

layout(location = 3) out vec3 position;
layout(location = 1) out vec3 normal;
layout(location = 2) out vec3 depth;
layout(location = 0) out vec3 color;

in vec3 position_worldspace;
in vec3 normal_worldspace;
in vec3 l;
in vec3 c;
 
void main(){

	position = position_worldspace;
	normal   = normal_worldspace;
	depth    = gl_FragCoord.zzz;
	float cosTheta = clamp(dot(normal_worldspace,l), 0, 1);

    color    = c * (cosTheta + 0.1);

}