#version 410 core

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 color;
uniform mat4 MVP;
uniform vec3 Light;

out vec3 n;
out vec3 l;
out vec3 c;

void main() {

    vec4 v = vec4(vertex,1);
    gl_Position = MVP * v;

    l = normalize(Light - vertex);
    n = normal;
    c = color;

}
