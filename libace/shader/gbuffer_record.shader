#<vertex-shader>
#version 120

// input variables
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

attribute vec3 in_pos;
attribute vec2 in_uv;
attribute vec3 in_vn;

varying vec2 frag_tex_coords;
varying vec3 frag_normal;
varying vec3 frag_position;

void main() {
    gl_Position     = proj * view * model * gl_Vertex;
    frag_tex_coords = in_uv;
    frag_normal     = normalize( ( model * vec4( in_vn, 0.0 ) ).xyz );
    frag_position   = vec3( model * gl_Vertex );
}

#<fragment-shader>
#version 120

uniform sampler2D tex;

varying vec2 frag_tex_coords;
varying vec3 frag_normal;
varying vec3 frag_position;

void main() {
    gl_FragData[0]  = vec4( 0 );                            // depth (ignore)
    gl_FragData[1]  = vec4( frag_position, 1 );             // pos
    gl_FragData[2]  = vec4( frag_normal, 1 );               // norm
    gl_FragData[3]  = texture2D( tex, frag_tex_coords );    // col
}
