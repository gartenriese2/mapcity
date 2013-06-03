#<vertex-shader>
#version 410

// input variables
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

layout( location = 0 ) in vec3 in_pos;
layout( location = 1 ) in vec2 in_uv;
layout( location = 2 ) in vec3 in_vn;

out vec2 frag_tex_coords;
out vec3 frag_normal;
out vec3 frag_position;

void main() {
	vec4 Vertex     = vec4( in_pos, 1.0 );
    gl_Position     = proj * view * model * Vertex;

    frag_tex_coords = in_uv;
    frag_normal     = normalize( ( model * vec4( in_vn, 0.0 ) ).xyz );
    frag_position   = ( model * Vertex ).xyz;
}

#<fragment-shader>
#version 410

uniform sampler2D tex;

in vec2 frag_tex_coords;
in vec3 frag_normal;
in vec3 frag_position;

out vec4 FragData[4];

void main() {
    FragData[0]  = vec4( 0.0 );                            // depth (ignore)
    FragData[1]  = vec4( frag_position, 1.0 );             // pos
    FragData[2]  = vec4( frag_normal, 1.0 );               // norm
    FragData[3]  = texture( tex, frag_tex_coords );        // col
}
