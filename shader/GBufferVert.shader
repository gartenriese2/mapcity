#version 410

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 color;

uniform mat4 MVP;
uniform vec3 Light;

out vec3 position_worldspace;
out vec3 normal_worldspace;
out vec3 l;
out vec3 c;

void main() {

    gl_Position         = MVP * vec4(vertex, 1.f);
    position_worldspace = vertex;
    normal_worldspace   = normal;
    l = normalize(Light - vertex);
    c = color;
    
}