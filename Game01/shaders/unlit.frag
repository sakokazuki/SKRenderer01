
#version 400


uniform sampler2DShadow ShadowMap;

in vec4 ShadowCoord;

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 UnlitColor;

void main(){
    float shadow = textureProj(ShadowMap, ShadowCoord);
//    FragColor = vec4(0.0, 1.0, 0.0, 1.0);
//    FragColor = vec4(ShadowCoord.x, ShadowCoord.y, 1.0, 1.0);
    FragColor = vec4(shadow, shadow, shadow, 1.0);
    UnlitColor = vec4(shadow, shadow, shadow, 1.0);

}
