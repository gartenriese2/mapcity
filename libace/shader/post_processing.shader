#<vertex-shader>
#version 410

// input variables
layout( location = 0 ) in vec3 vertPos_modelspace;
out vec2 tex_coords;

void main() {
    gl_Position = vec4( vertPos_modelspace, 1.0 );
    tex_coords  = ( vertPos_modelspace.xy + vec2( 1.0, 1.0 ) ) * 0.5;
}

#<fragment-shader>
#version 410

uniform sampler2D tex;

uniform sampler2D depthTexture;
uniform sampler2D colorTexture;
uniform sampler2D normalTexture;
uniform sampler2D positionTexture;

uniform float screenwidth;
uniform float screenheight;

in vec2 tex_coords;
out vec4 FragColor;

vec4 bloom( sampler2D tex, vec2 coords ) {
    vec4 sum = vec4(0);
    int size = 3;
    for( int i = -size; i < size; ++i ) {
        for( int j = -size; j < size; ++j ) {
            sum += texture( tex, tex_coords + vec2( j, i ) * 0.004 ) * 0.25;
        }
    }
    
    if( texture( tex, tex_coords ).r < 0.3) {
       sum = sum * sum * 0.012 + texture( tex, tex_coords );
    }
    else {
        if ( texture( tex, tex_coords ).r < 0.5) {
            sum = sum * sum * 0.009 + texture( tex, tex_coords );
        }
        else {
            sum = sum * sum * 0.0075 + texture( tex, tex_coords );
        }
    }

    return sum;
}

vec4 antialiasing( sampler2D normal, sampler2D color, vec2 coords, vec2 p ) {
    float weight = 1.0;

    vec4 r       = texture( normal, tex_coords );
    float factor = 0;
    for( int x = -1; x <= 1; ++x ) {
        for( int y = -1; y <= 1; ++y ) {
            vec4 t = texture( normal, tex_coords + vec2( x * p.x, y * p.y ) );
            t -= r;
            factor += dot( t, t );
        }
    }

    factor   = min( 1.0, factor ) * weight;
    vec4 col = vec4( 0 );
    vec4 c   = bloom( color, tex_coords );
    for( int x = -2; x <= 2; ++x ) {
        for( int y = -2; y <= 2; ++y ) {
            col += texture( color, tex_coords + vec2( x * p.x, y * p.y ) * factor );
        }
    }

    return ( col + 3.0 * c ) * 0.1;
}

void main() {
    vec2 pixelsize = vec2( 1.0 / screenwidth, 1.0 / screenheight );
    vec4 outcolor  = antialiasing( normalTexture, tex, tex_coords, pixelsize );
    FragColor = outcolor;
}
