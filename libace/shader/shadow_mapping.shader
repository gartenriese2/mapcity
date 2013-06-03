#<vertex-shader>
#version 410

// input variables
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

layout( location = 0 ) in vec3 in_pos;
layout( location = 1 ) in vec2 in_uv;
layout( location = 2 ) in vec3 in_vn;

void main() {
	vec4 Vertex     = vec4( in_pos, 1.0 );
    gl_Position     = proj * view * model * Vertex;
}

#<fragment-shader>
#version 410

out vec4 FragColor;

void main() {
    FragColor    = vec4( 1.0 );
}
