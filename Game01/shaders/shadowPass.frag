#version 400

uniform sampler2DShadow ShadowMap;

in vec4 ShadowCoord;
in vec2 TexCoord;
in vec3 Normal;
in vec3 LightDirection;

uniform sampler3D OffsetTex;
uniform float Radius;
uniform vec3 OffsetTexSize;


layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 ShadowmapColor;

void main() {
	vec3 n = normalize(Normal);
	vec3 l = normalize(LightDirection);
	float cosTheta = clamp(dot(n, l), 0.0, 1.0);

	float bias = 0.005*tan(acos(cosTheta));
	
	ivec3 offsetCoord;
	offsetCoord.xy = ivec2(mod(gl_FragCoord.xy, OffsetTexSize.xy));
	float sum = 0.0;
	int samplesDiv2 = int(OffsetTexSize.z);
	vec4 sc = ShadowCoord;

	for(int i=0; i<4; i++){
		offsetCoord.z = i;
		vec4 offsets = texelFetch(OffsetTex, offsetCoord, 0) * Radius * ShadowCoord.w;

		sc.xy = ShadowCoord.xy + offsets.xy;
		sum += texture( ShadowMap, vec3(sc.xy, (sc.z-bias)/sc.w));
		sc.xy = ShadowCoord.xy + offsets.zw;
		sum += texture( ShadowMap, vec3(sc.xy, (sc.z-bias)/sc.w));

	}
	float shadow = sum / 8.0;
	
	if(shadow != 1.0 && shadow != 0.0){
		for(int i=0; i<4; i++){
			offsetCoord.z = i;
			vec4 offsets = texelFetch(OffsetTex, offsetCoord, 0) * Radius * ShadowCoord.w;

			sc.xy = ShadowCoord.xy + offsets.xy;
			sum += texture( ShadowMap, vec3(sc.xy, (sc.z-bias)/sc.w));
			sc.xy = ShadowCoord.xy + offsets.zw;
			sum += texture( ShadowMap, vec3(sc.xy, (sc.z-bias)/sc.w));

		}
		shadow = sum/float(samplesDiv2 * 2.0);
	}

	shadow += 0.3;
	shadow = clamp(shadow, 0.0, 1.0);
	
    FragColor = vec4(vec3(shadow), 1.0);
	ShadowmapColor = FragColor;


}
