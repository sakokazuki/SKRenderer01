#version 400


uniform sampler2DShadow ShadowMap;
in vec3 Position;
in vec3 Normal;
in vec4 ShadowCoord;

layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 ShadowColor;

subroutine void RenderPassType();
subroutine uniform RenderPassType RenderPass;

subroutine(RenderPassType)
void shadeWithShadow(){
    
    float shadow = textureProj(ShadowMap, ShadowCoord);

    FragColor = vec4(shadow, shadow, shadow, 1.0);
    ShadowColor = vec4(shadow, shadow, shadow, 1.0);
    FragColor = vec4(ShadowCoord.x, ShadowCoord.y, 1.0, 1.0);
}

subroutine(RenderPassType)
void recordDepth(){
    
}

void main(){
    RenderPass();
}
