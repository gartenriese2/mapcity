#version 410

layout(location = 0) in vec3 vertex;

uniform mat4 MVP;
uniform mat4 DepthBiasMVP;

out vec4 ShadowCoord;

void main() {

    gl_Position = MVP * vec4(vertex, 1.f);
    ShadowCoord = DepthBiasMVP * vec4(vertex, 1.f);

}
