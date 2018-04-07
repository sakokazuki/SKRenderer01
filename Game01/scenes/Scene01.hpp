//
//  Scene01.hpp
//  Game01
//
//  Created by kazuki sako on 2018/02/07.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#ifndef Scene01_hpp
#define Scene01_hpp

#include <stdio.h>
#include "Scene.hpp"
#include <vector>

#include "../system/ShaderFunc.hpp"


#include "../objects/Quad.hpp"

#include "../lights/Light.hpp"
#include "../camera/Camera.hpp"
#include "../meshes/TorusMesh.hpp"
#include "../meshes/PlaneMesh.hpp"
#include "../meshes/Mesh.hpp"

#include "../renderpass/ShadowmapPass.hpp"
#include "../renderpass/RecordLightDepthPass.hpp"
#include "../renderpass/GBufferPass.hpp"
#include "../renderpass/ShadingPass.hpp"

#include "../system/zTexture.hpp"
#include "../meshMaterials/TextureMeshMaterial.hpp"

class Scene01:public Scene{
private:
    
    PlaneMesh* plane;
    TorusMesh* torus;

    GLuint shadowFBO;
    GLuint depthTex;
    GLuint deferredFBO;
    GLuint depthBuf, posTex, normTex, colorTex, shadowTex;
    GLuint shadowmapFBO, unlitColorTex;
    
    Light* light;
    Camera* camera;
    std::vector<Mesh*> meshes;
    RenderPass* shadowmapPass;
    RenderPass* recordLightDepthPass;
    RenderPass* gBufferPass;
    RenderPass* shadingPass;
    
    TextureMeshMaterial *texmat1;
    TextureMeshMaterial *texmat2;
    
    zTexture greenTex;
    zTexture groundTex;
    GLuint whiteTex;
    
    
public:
    Scene01(int ww, int wh);
    void render() const override;
};


#endif /* Scene01_hpp */
