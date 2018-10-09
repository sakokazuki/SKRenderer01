//
//  Renderer01.hpp
//  Game01
//
//  Created by kazuki sako on 2018/02/07.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#ifndef Renderer01_hpp
#define Renderer01_hpp

#include <stdio.h>
#include "Renderer.hpp"
#include <vector>

#include "../system/ShaderFunc.hpp"

#include "../objects/Quad.hpp"

#include "../renderpass/ShadowmapPass.hpp"
#include "../renderpass/RecordLightDepthPass.hpp"
#include "../renderpass/GBufferPass.hpp"
#include "../renderpass/PbrShadingPass.hpp"
#include "../renderpass/TestPass.h"

class Renderer01:public Renderer{
private:

    GLuint shadowFBO;
    GLuint depthTex;
    GLuint deferredFBO;
    GLuint depthBuf, shadowDepthBuf, posTex, normTex, colorTex, shadowTex;
    GLuint shadowmapFBO, unlitColorTex;
    
    RenderPass* shadowmapPass;
    RenderPass* recordLightDepthPass;
    RenderPass* gBufferPass;
    RenderPass* shadingPass;
	RenderPass* testPass;
    
    GLuint whiteTex;
    
public:
    Renderer01(int ww, int wh);
    void render(Scene::Scene* scene) const override;
    void addRenderer();
};


#endif /* Renderer01_hpp */
