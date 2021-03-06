
#version 400

layout(location = 0) in vec3 VertexPosition;
//layout(location = 1) in vec3 VertexNormal;

uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 MVP;

void main(){
    
    gl_Position = MVP * vec4(VertexPosition, 1.0);
}
