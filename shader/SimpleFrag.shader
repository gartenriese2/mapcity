#version 330 core

in vec3 n;
in vec3 l;
in vec3 c;
out vec3 color;
 
void main(){
    float cosTheta = clamp(dot(n,l), 0, 1);
    color = c * (cosTheta + 0.1);
}
