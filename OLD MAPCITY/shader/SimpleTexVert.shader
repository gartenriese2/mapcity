#version 410

layout(location = 0) in vec3 vertex;

out vec2 texCoord;

void main() {

    gl_Position = vec4(vertex, 1.0);

    texCoord = ivec2(vertex.xy) * 0.5 + 0.5;

}
