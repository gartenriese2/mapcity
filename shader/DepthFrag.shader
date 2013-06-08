#version 410 core

layout(pixel_center_integer) in vec4 gl_FragCoord;

out vec3 depth;
 
void main(){
   
   depth = gl_FragCoord.zzz * 200.f - vec3(199,199,199);

}
