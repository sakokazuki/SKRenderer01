//
//  SceneDeferred.hpp
//  Game01
//
//  Created by kazuki sako on 2018/01/29.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#ifndef SceneDeferred_hpp
#define SceneDeferred_hpp

#include <stdio.h>
#include "Scene.hpp"

#include "../system/zTexture.hpp"
#include "../system/ShaderFunc.hpp"
#include "../materials/DeferredMaterial.hpp"

#include "../objects/Quad.hpp"
#include "../objects/Torus.hpp"


class SceneDeferred:public Scene{
private:
    Quad* quad;
    DeferredMaterial* deferredMat;
    Torus* torus;
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
    GLuint deferredFBO;
    GLuint depthBuf, posTex, normTex, colorTex;
public:
    SceneDeferred(int ww, int wh);
    void render() const override;
};



#endif /* SceneDeferred_hpp */
