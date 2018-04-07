#version 400

in vec2 TexCoord;

uniform sampler2D RenderTex;

layout( location = 0 ) out vec4 FragColor;

void main() {
    vec4 texColor = texture( RenderTex, TexCoord );
    FragColor = texColor;
}

