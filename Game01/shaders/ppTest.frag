#version 400

layout (location=0) out vec4 FragColor;
layout (location=1) out vec4 FboColor;

subroutine vec3 passType();
subroutine uniform passType passModel;

uniform sampler2D MainTex;
in vec2 TexCoord;

subroutine(passType)
vec3 pass0(){
	vec4 col = texture(MainTex, TexCoord);
	return col.rgb*1.0;
}

subroutine(passType)
vec3 pass1(){
	vec4 col = texture(MainTex, TexCoord);
	if(TexCoord.x < 0.5){
		return vec3(col.r);
	}
	return col.xyz;
	
}

void main() {
	vec3 color =  passModel();
	FragColor = vec4(color, 1.0);

	FboColor = FragColor;
}
