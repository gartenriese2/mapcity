#<vertex-shader>
#version 410

// input variables
layout( location = 0 ) in vec3 vertPos_modelspace;
layout( location = 1 ) in vec3 in_uv;

uniform mat4 model;
uniform mat4 proj;
uniform mat4 view;

out vec2 tex_coords;
out vec3 cam_pos;

void main() {
    gl_Position = vec4( vertPos_modelspace, 1.0 );
    tex_coords  = ( vertPos_modelspace.xy + vec2( 1.0, 1.0 ) ) * 0.5;
    cam_pos     = vec3( view[0][3], view[1][3], view[2][3] );
}

#<fragment-shader>
#version 410

uniform sampler2D depthTexture;
uniform sampler2D colorTexture;
uniform sampler2D normalTexture;
uniform sampler2D positionTexture;

uniform sampler2D randomTexture;

uniform vec3  light_pos[100];
uniform vec3  light_color[100];
uniform float light_radius[100];
uniform float light_intensity[100];
uniform float light_count;

uniform float screenwidth;
uniform float screenheight;

uniform float debug;

in vec2 tex_coords;
in vec3 cam_pos;

out vec4 FragColor;

float doao( vec2 coords, vec2 v, sampler2D P, sampler2D N ) {
    float scale     = 0.001;
    float bias      = 0.01;
    float intensity = 0.5;

    vec3 pt = texture( P, coords ).xyz; // position
    vec3 nt = texture( N, coords ).xyz; // normal
    vec3 pr = texture( P, coords + v ).xyz;
    vec3 d  = normalize( pr - pt );
    float l = distance( pr, pt );

    return max( dot( nt, d ) - bias, 0.0 ) * ( 1.0 / ( 1.0 + l ) ) * intensity;
}

vec4 ssao( sampler2D P, sampler2D N, sampler2D R, vec2 coords, vec2 p ) {
    float ao     = 0.0;
    float radius = 0.1;
    vec4 pt = texture( P, coords ); // position
    vec4 nt = texture( N, coords ); // normal
    vec4 rt = texture( R, coords * p * vec2( 64.0, 64.0) ); // random

    vec2[4] vr = vec2[]( vec2( 1, 0 ), vec2( -1, 0 ), vec2( 0, 1 ), vec2( 0, -1 ) );

    radius /= pt.z; 

    int iter = 4;
    for( int i = 0; i < iter; ++i ) {
        vec2 c1 = reflect( vr[i], rt.xy ) * radius;
        vec2 c2 = vec2( c1.x*0.707 - c1.y*0.707, c1.x*0.707 + c1.y*0.707 );

        ao += doao( coords, c1*0.25, P, N );
        ao += doao( coords, c2*0.5, P, N );
        ao += doao( coords, c1*0.75, P, N );
        ao += doao( coords, c2, P, N );
    }

    ao /= ( iter*4 );
    return vec4( ao, ao, ao, 1.0 );
}

void main() {
    // avoid branching [if,for,while] wherever possible!

    vec4 depth  = texture( depthTexture,    tex_coords );
    vec4 pos    = texture( positionTexture, tex_coords );
    vec4 normal = texture( normalTexture,   tex_coords );
    vec4 color  = texture( colorTexture,    tex_coords );

    vec4 col_ambient     = vec4( 0.05, 0.05, 0.05, 1.0 );
    vec4 col_diffuse     = vec4( 0.0 );
    vec4 col_specular    = vec4( 0.0 );

    for( int i = 0; i < int( light_count ); ++i ) {
        float intensity      = light_intensity[i];
        float distance       = max( distance( light_pos[i], pos.xyz ), 0.0 );
        float attenuation    = 1.0 / pow( distance / light_radius[i] + 1.0, 2.0 );

        vec3 N = normalize( normal.xyz );
        vec3 L = normalize( light_pos[i] - pos.xyz );
        vec3 V = normalize( cam_pos - pos.xyz );
        vec3 R = normalize( reflect( L, N ) );
        
        float diffuse_factor = max( dot( N, L ), 0.0 );
        float specular_factor= pow( max( dot( R, V ), 0.0 ), 8.0 );

        col_specular += vec4( light_color[i], 1.0 ) * specular_factor * attenuation;
        col_diffuse  += vec4( light_color[i], 1.0 ) * diffuse_factor * attenuation;
    }

    vec2 pixelsize = vec2( 1.0 / screenwidth, 1.0 / screenheight );
    vec4 ao  = ssao( positionTexture, normalTexture, randomTexture, tex_coords, pixelsize );

    FragColor = color * ( ( col_ambient - 0.2*ao ) + col_diffuse + col_specular );

    if( debug == 1.0 ) {
        FragColor = depth;
    }
    else if( debug == 2.0 ) {
        FragColor = pos;
    }
    else if( debug == 3.0 ) {
        FragColor = normal;
    }
    else if( debug == 4.0 ) {
        FragColor = color;
    }
    else if( debug == 5.0 ) {
        FragColor = ao;
    }
}
