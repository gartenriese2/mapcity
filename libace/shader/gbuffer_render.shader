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
uniform float light_radius[100];
uniform float light_intensity[100];
uniform float light_count;

uniform float debug;

varying vec2 tex_coords;
varying vec3 cam_pos;

vec4 bloom( sampler2D tex, vec2 coords ) {
    vec4 sum = vec4(0);
    int size = 3;
    for( int i = -size; i < size; ++i ) {
        for( int j = -size; j < size; ++j ) {
            sum += texture2D( tex, tex_coords + vec2( j, i ) * 0.004 ) * 0.25;
        }
    }
    
    if( texture2D( tex, tex_coords ).r < 0.3) {
       sum = sum * sum * 0.012 + texture2D( tex, tex_coords );
    }
    else {
        if ( texture2D( tex, tex_coords ).r < 0.5) {
            sum = sum * sum * 0.009 + texture2D( tex, tex_coords );
        }
        else {
            sum = sum * sum * 0.0075 + texture2D( tex, tex_coords );
        }
    }

    return sum;
}

float ssao( sampler2D P, sampler2D N, vec2 coords ) {
    vec4 refpos     = texture2D( P, coords );
    float occlusion = 0.0;

    int k = 1;
    for( int x = -k; x <= k; ++x ) {
        for( int y = -k; y <= k; ++y ) {
            vec2 offset    = vec2( float(x)/640.0, float(y)/480.0 );

            vec4 pos       = texture2D( P, coords + offset ); 
            vec4 normal    = texture2D( N, coords + offset ); 

            vec4 V         = normalize( refpos - pos );
            float d        = distance( refpos, pos );

            occlusion = max( dot( normal, V ), 0.0 ) * ( 1.0 / ( 1.0 + d ) );
        }
    }

    return occlusion;
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
        float distance       = max( distance( light_pos[i], pos.xyz ), 0.0 );
        float attenuation    = 1.0 / pow( distance / light_radius[i] + 1.0, 2.0 );

        vec3 L               = normalize( light_pos[i] - pos.xyz );
        vec3 eye_dir         = normalize( cam_pos - pos.xyz );
        vec3 v_half_vector   = normalize( L + eye_dir );
        
        float diffuse_factor = max( dot( normal.xyz, L ), 0.0 );
        float specular_factor= pow( max( dot( normal.xyz, v_half_vector ), 0.0 ), 10.0 );

        col_specular += vec4( light_color[i], 1.0 ) * specular_factor * attenuation;
        col_diffuse  += vec4( light_color[i], 1.0 ) * diffuse_factor * attenuation;
    }

    // float o = ssao( positionTexture, normalTexture, tex_coords );
    // col_ambient -= vec4( o );
    vec4 b  = bloom( colorTexture, tex_coords );
    gl_FragColor = b * ( col_ambient + col_diffuse + col_specular );

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
