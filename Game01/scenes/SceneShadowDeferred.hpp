//
//  SceneShadowDeferred.hpp
//  Game01
//
//  Created by kazuki sako on 2018/02/03.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#ifndef SceneShadowDeferred_hpp
#define SceneShadowDeferred_hpp

#include <stdio.h>
#include "Scene.hpp"


#include "../system/zTexture.hpp"
#include "../system/ShaderFunc.hpp"
#include "../materials/ShadowmapPassMaterial.hpp"
#include "../materials/DeferredPassMaterial.hpp"
#include "../materials/DeferredMaterial.hpp"
#include "../materials/UnlitMaterial.hpp"

#include "../objects/Quad.hpp"
#include "../objects/Torus.hpp"
#include "../objects/Plane.hpp"
#include "../lights/Light.hpp"

#include "../camera/Camera.hpp"

class SceneShadowDeferred:public Scene{
private:
    Quad* quad;

    ShadowmapPassMaterial* shadowmappass;
    DeferredPassMaterial* deferredpass;
    DeferredMaterial* deferredmat;
    UnlitMaterial* unlitmat;
    Torus* torus;
    Plane* plane;
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
    GLuint shadowFBO;
    GLuint depthTex;
    GLuint deferredFBO;
    GLuint shadowmapFBO;
    GLuint depthBuf, posTex, normTex, colorTex, shadowTex;
    GLuint simpleFBO, unlitColorTex, unlitColorTex2;
    Light* light;
    Camera* camera;
    void drawScene() const;
    void drawScene2() const;
    void drawScene3() const;

public:
    SceneShadowDeferred(int ww, int wh);
    void render() const override;
};


#endif /* SceneShadowDeferred_hpp */

