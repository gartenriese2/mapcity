/*
*
*   Copyright (c) 2013, Jan Doerntlein.
*   All rights reserved.
*
*/

#include "shader.h"

namespace ace {

void Shader::printShaderInfoLog( GLuint obj ) {
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;
    std::string error = "ShaderInfoLog: ";

    glGetShaderiv( obj, GL_INFO_LOG_LENGTH, &infologLength );
    if ( infologLength > 0 )
    {
        infoLog = new char[ infologLength ];
        glGetShaderInfoLog( obj, infologLength, &charsWritten, infoLog );
        error += infoLog;
        delete[] infoLog;

        g_AceLog.setError( error );
    }
}

void Shader::printProgramInfoLog( GLuint obj ) {
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;
    std::string error = "ShaderProgramInfoLog: ";

    glGetProgramiv( obj, GL_INFO_LOG_LENGTH, &infologLength );
    if ( infologLength > 0 )
    {
        infoLog = new char[ infologLength ];
        glGetProgramInfoLog( obj, infologLength, &charsWritten, infoLog );
        error += infoLog;
        delete[] infoLog;

        g_AceLog.setError( error );
    }
}

Shader::Shader( const std::string filename ) {
   program = 0;
   load( filename );
}

Shader::Shader() {
   program = 0;
}

Shader::~Shader() {

}

bool Shader::load( const std::string filename ) {
   std::ifstream file( filename.c_str(), std::ios::in );
   if( !file.good() ) {
      g_AceLog.setError( "Shader: could not open file" );
      return false;
   }

   int mode = UNDEF_MODE;

   while( !file.eof() ) {
      std::string ln;
      getline( file, ln );

      // switch mode
      if( ln == "#<vertex-shader>" ) {
         mode = VERTEX_MODE;
      } 
      else if ( ln == "#<fragment-shader>" ) {
         mode = FRAGMENT_MODE;
      } 

      // check comment
      if( ln.find( "#" ) != ln.npos ) {

        // ignore

      } else {

         // check what to do
         if( mode == VERTEX_MODE ) {
            m_vertex += ln + "\n";
         } 
         else if( mode == FRAGMENT_MODE ) {
            m_fragment += ln + "\n";
         }

      }
   }

   file.close();

   return compile();
}

bool Shader::compile() {
   GLuint v = glCreateShader( GL_VERTEX_SHADER );
   GLuint f = glCreateShader( GL_FRAGMENT_SHADER );

   const char *vs = m_vertex.c_str();
   const char *fs = m_fragment.c_str();
   
   glShaderSource( v, 1, &vs, NULL );
   glShaderSource( f, 1, &fs, NULL );
   
   glCompileShader( v ); 
   glCompileShader( f );
   
   program = glCreateProgram();
   glAttachShader( program, v ); 
   glAttachShader( program, f );
   glLinkProgram( program );
   
   printShaderInfoLog( v );
   printShaderInfoLog( f );
   printProgramInfoLog( program );

   return true;
}

void Shader::bind() {
   glUseProgram( program );
}

void Shader::unbind() {
   glUseProgram( 0 );
} 

void Shader::addAttribute( const std::string attr, unsigned int v ) {
   m_attributeList[ attr ] = v;
   glBindAttribLocation( program, v, attr.c_str() );
}

void Shader::addUniform( const std::string uniform, float v ) {
   m_uniformList[ uniform ] = glGetUniformLocation( program, uniform.c_str() );
   glUniform1f( m_uniformList[ uniform ], v );
}

void Shader::addUniform( const std::string uniform, unsigned int v ) {
   m_uniformList[ uniform ] = glGetUniformLocation( program, uniform.c_str() );
   glUniform1i( m_uniformList[ uniform ], v );
}

void Shader::addUniform( const std::string uniform, float *v ) {
   m_uniformList[ uniform ] = glGetUniformLocation( program, uniform.c_str() );
   glUniformMatrix4fv( m_uniformList[ uniform ], 1, GL_FALSE, v );
}

void Shader::addUniform( const std::string uniform, glm::mat4& v ) {
   m_uniformList[ uniform ] = glGetUniformLocation( program, uniform.c_str() );
   glUniformMatrix4fv( m_uniformList[ uniform ], 1, GL_FALSE, glm::value_ptr( v ) );
}

void Shader::addUniform( const std::string uniform, glm::vec3& v ) {
   m_uniformList[ uniform ] = glGetUniformLocation( program, uniform.c_str() );
   glUniform3fv( m_uniformList[ uniform ], 1, glm::value_ptr( v ) );
}

void Shader::addUniform( const std::string uniform, glm::vec4& v ) {
   m_uniformList[ uniform ] = glGetUniformLocation( program, uniform.c_str() );
   glUniform4fv( m_uniformList[ uniform ], 1, glm::value_ptr( v ) );
}


}