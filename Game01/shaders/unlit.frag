
#version 400


uniform sampler2DShadow ShadowMap;
//uniform sampler2D ShadowMap;

in vec4 ShadowCoord;
in vec2 TexCoord;

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 UnlitColor;

void main(){
    float shadow = textureProj(ShadowMap, ShadowCoord);
    
//    vec4 shadowColor = texture(ShadowMap, TexCoord);
//    FragColor = shadowColor;
//    FragColor= vec4(1.0);
//    if(diff >= 0){
//        FragColor = vec4(0.0, 0.0, 0.0, 1.0);
//    }
    

    FragColor = vec4(shadow, shadow, shadow, 1.0);
    UnlitColor = vec4(shadow, shadow, shadow, 1.0);

}
