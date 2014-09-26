#version 410

layout(location = 4) out vec3 shadow;
 
void main() {

	shadow = (gl_FragCoord.zzz - 0.999) * 1000;

}