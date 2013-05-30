#version 330 core

in vec3 n;
in vec3 l;
out vec3 color;
 
void main(){
    float cosTheta = clamp(dot(n,l), 0, 1);
    color = vec3(1,0,0) * cosTheta + vec3(0.1,0,0);
}
