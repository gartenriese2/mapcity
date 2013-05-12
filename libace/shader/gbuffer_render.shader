#<vertex-shader>
#version 120

// input variables
attribute vec3 vertPos_modelspace;
attribute vec2 in_uv;

uniform mat4 model;
uniform mat4 proj;
uniform mat4 view;

varying vec2 tex_coords;
varying vec3 cam_pos;

void main() {
    gl_Position = vec4( vertPos_modelspace, 1 );
    tex_coords  = ( vertPos_modelspace.xy + vec2( 1, 1 ) ) * 0.5;
    cam_pos     = vec3( view[0][3], view[1][3], view[2][3] );
}

#<fragment-shader>
#version 120

uniform sampler2D depthTexture;
uniform sampler2D colorTexture;
uniform sampler2D normalTexture;
uniform sampler2D positionTexture;

uniform vec3  light_pos[100];
uniform vec3  light_color[100];
uniform float  light_radius[100];
uniform float  light_intensity[100];
uniform float light_count;

uniform float debug;

varying vec2 tex_coords;
varying vec3 cam_pos;

vec4 blur( sampler2D tex, vec2 coords, int size ) {
    vec3 col = vec3( 0, 0, 0 );
    int b = int( float( size-1 ) / 2.0 );
    for( int x = -b; x <= b; ++x ) {
        for( int y = -b; y <= b; ++y ) {
            vec2 offset = vec2( float(x)/640.0, float(y)/480.0 );
            vec4 col    = texture2D( tex, coords + offset ); 
            col.xyz    += dot( col.xyz, col.xyz );           
        }
    }
    return vec4( col.xyz * ( 1.0 / float( size * size ) ), 1 );
}

void main() {
    vec4 depth  = texture2D( depthTexture,    tex_coords );
    vec4 pos    = texture2D( positionTexture, tex_coords );
    vec4 normal = texture2D( normalTexture,   tex_coords );
    vec4 color  = texture2D( colorTexture,    tex_coords );

    vec4 col_ambient     = vec4( 0.05, 0.05, 0.05, 1.0 );
    vec4 col_diffuse     = vec4( 0.0 );
    vec4 col_specular    = vec4( 0.0 );

    for( int i = 0; i < int( light_count ); ++i ) {
        float intensity      = light_intensity[i];
        float distance       = distance( light_pos[i], pos.xyz );
        // if( distance > light_radius[i] ) {}

        vec3 light_dir       = normalize( light_pos[i] - pos.xyz );
        vec3 eye_dir         = normalize( vec3( pos.rgb ) - cam_pos );

        float diffuse_factor = dot( normal.xyz, light_dir );

        if( diffuse_factor > 0.0 ) {
            col_diffuse += vec4( light_color[i], 1.0 ) * diffuse_factor * intensity;

            vec3 light_reflect    = normalize( reflect( -light_dir, normal.xyz ) );
            vec3 v_half_vector    = normalize( light_dir + eye_dir );
            float specular_factor = pow( dot( v_half_vector, light_reflect ), 10.0 );  
            if( specular_factor > 0.0 ) {
                col_specular += vec4( light_color[i], 1.0 ) * specular_factor * intensity;
            }
        }
    }
    
    gl_FragColor = color * ( col_ambient + col_diffuse + col_specular );
    
    if( debug == 1.0 ) {
        gl_FragColor = depth;
    }
    else if( debug == 2.0 ) {
        gl_FragColor = pos;
    }
    else if( debug == 3.0 ) {
        gl_FragColor = normal;
    }
    else if( debug == 4.0 ) {
        gl_FragColor = color;
    }
}
