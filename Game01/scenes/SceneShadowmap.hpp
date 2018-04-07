//
//  SceneShadowmap.hpp
//  Game01
//
//  Created by kazuki sako on 2018/01/29.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#ifndef SceneShadowmap_hpp
#define SceneShadowmap_hpp

#include <stdio.h>
#include "Scene.hpp"

#include "../system/zTexture.hpp"
#include "../system/ShaderFunc.hpp"
#include "../materials/DeferredMaterial.hpp"
#include "../materials/ShadowmapMaterial.hpp"

#include "../objects/Quad.hpp"
#include "../objects/Torus.hpp"
#include "../objects/Plane.hpp"




class SceneShadowmap:public Scene{
private:
    Quad* quad;
    DeferredMaterial* deferredMat;
    ShadowmapMaterial* shadowmapMat;
    Torus* torus;
    Plane* plane;
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
    GLuint shadowFBO;
    GLuint depthTex;
    
    void drawScene(int pass) const;
    
public:
    SceneShadowmap(int ww, int wh);
    void render() const override;
};


#endif /* SceneShadowmap_hpp */
