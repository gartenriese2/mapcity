#version 410

in vec4 ShadowCoord;
uniform sampler2D shadowMap;

out vec3 color;
 
void main(){

	float visibility = 1.0;
	if ( texture( shadowMap, ShadowCoord.xy ).z  <  ShadowCoord.z){
    	visibility = 0.0;
	}

	color = vec3(visibility,0,0);

}
