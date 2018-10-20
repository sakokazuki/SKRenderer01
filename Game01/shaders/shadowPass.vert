
#version 400

layout(location = 0) in vec3 VertexPosition;
layout(location = 1) in vec3 VertexNormal;
layout(location = 2) in vec2 VertexTexCoord;

out vec4 ShadowCoord;
out vec2 TexCoord;
out vec3 Normal;
out vec3 LightDirection;

uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 MVP;
uniform mat4 ShadowMatrix;
uniform vec3 WorldLightDirection;
uniform mat4 ViewMatrix;

void main(){
    ShadowCoord = ShadowMatrix * vec4(VertexPosition, 1.0);
    TexCoord = VertexTexCoord;
	Normal = normalize(NormalMatrix * VertexNormal);
	LightDirection = (ViewMatrix * vec4(WorldLightDirection, 0.0)).xyz;
    gl_Position = MVP * vec4(VertexPosition, 1.0);
}