#version 400

layout (location=0) out vec4 FragColor;

in vec2 TexCoord;
uniform sampler2D ShadowMap;
uniform vec2 BlurScale;

void main() {
	vec4 color = vec4(0.0);
	vec2 bs = vec2(0.1, 0.0);
	color += texture2D(ShadowMap, TexCoord + (vec2(-3.0) * BlurScale.xy)) * (1.0/64.0);
	color += texture2D(ShadowMap, TexCoord + (vec2(-2.0) * BlurScale.xy)) * (6.0/64.0);
	color += texture2D(ShadowMap, TexCoord + (vec2(-1.0) * BlurScale.xy)) * (15.0/64.0);
	color += texture2D(ShadowMap, TexCoord + (vec2(0.0) * BlurScale.xy)) * (20.0/64.0);
	color += texture2D(ShadowMap, TexCoord + (vec2(1.0) * BlurScale.xy)) * (15.0/64.0);
	color += texture2D(ShadowMap, TexCoord + (vec2(2.0) * BlurScale.xy)) * (6.0/64.0);
	color += texture2D(ShadowMap, TexCoord + (vec2(3.0) * BlurScale.xy)) * (1.0/64.0);
    FragColor = color;
}
