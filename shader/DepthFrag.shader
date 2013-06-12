#version 410

out vec3 color;
 
void main(){

	color = gl_FragCoord.xyz;
	color = vec3(1,0,0);

}