//
//  ShadowmapMaterial.hpp
//  Game01
//
//  Created by kazuki sako on 2018/01/30.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#ifndef ShadowmapMaterial_hpp
#define ShadowmapMaterial_hpp

#include <stdio.h>
#include "ShaderMaterial.hpp"
#include "../system/frustum.h"

class ShadowmapMaterial:public ShaderMaterial{
private:
    GLint KdLoc, KsLoc, KaLoc, ShininessLoc, lightPositionLoc, lightIntensityLoc, shadowmapLoc, shadowMatrixLoc;
    GLfloat lightIntensity[3] = {0.85f, 0.85f, 0.85f};
    GLfloat Kd[3] = {0.9f, 0.9f, 0.9f};
    GLfloat Ks[3] = {0.1f, 0.1f, 0.1f};
    GLfloat Ka[3] = {0.1f, 0.1f, 0.1f};
    GLfloat Shininess = 1.0;
    glm::vec4 lightPosition;
    GLuint pass1Index, pass2Index;
    
    
    Frustum *lightFrustum;
    mat4 lightPV;
    mat4 shadowBias;
    float angle;
    
public:
    ShadowmapMaterial();
    void update(int passIndex, glm::mat4 viewMatrix, glm::mat4 projectionMatrix);
};




#endif /* ShadowmapMaterial_hpp */


