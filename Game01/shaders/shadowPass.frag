
#version 400


uniform sampler2DShadow ShadowMap;
//uniform sampler2D ShadowMap;

in vec4 ShadowCoord;
in vec2 TexCoord;

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 UnlitColor;

void main(){
    float bias = 0.0003;
    float shadow = texture( ShadowMap, vec3(ShadowCoord.xy, (ShadowCoord.z-bias)/ShadowCoord.w));

	shadow = 1.0;
	if ( texture( shadowMap, ShadowCoord.xy ).z  <  ShadowCoord.z){
		shadow = 0.0;
	}
    FragColor = vec4(shadow, shadow, 0.0, 1.0);
    UnlitColor = vec4(shadow, shadow, 0.0, 1.0);

}
