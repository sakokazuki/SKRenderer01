#version 400

//uniform sampler2DShadow ShadowMap;
uniform sampler2D ShadowMap;

in vec4 ShadowCoord;
in vec2 TexCoord;
in vec3 Normal;
in vec3 LightDirection;

uniform sampler3D OffsetTex;
uniform float Radius;
uniform vec3 OffsetTexSize;
uniform float ShadowBleedRedutionAmount;
uniform float MinShadowVariance;
uniform vec3 ShadowColor;

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 ShadowmapColor;

float linstep(float low, float high, float v){
	return clamp((v-low)/(high-low), 0.0, 1.0);
}

void main(){
	float shadow = step(ShadowCoord.z, texture2D(ShadowMap, ShadowCoord.xy).r);

	float compare = ShadowCoord.z;

	vec2 moments = texture2D(ShadowMap, ShadowCoord.xy).xy;
	
	float p = step(compare, moments.x);
	float variance = max(moments.y - moments.x * moments.x, MinShadowVariance);

	float d = compare - moments.x;
	float pMax = linstep(ShadowBleedRedutionAmount, 1.0, variance / (variance + d*d));
	shadow = max(p, pMax);
	
	vec3 shadowColor = ShadowColor.rgb + vec3(shadow);
	shadowColor = clamp(shadowColor, 0, 1);

	FragColor = vec4(shadowColor, 1.0);
	ShadowmapColor = FragColor;	
}
