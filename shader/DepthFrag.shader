#version 410

out vec3 color;
 
void main(){

	color = (gl_FragCoord.zzz - 0.97) * 10.0;
	//color = vec3(1,0,0);

}