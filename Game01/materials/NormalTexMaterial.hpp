//
//  NormalTexMaterial.hpp
//  Game01
//
//  Created by kazuki sako on 2018/01/25.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#ifndef NormalTexMaterial_hpp
#define NormalTexMaterial_hpp

#include <stdio.h>
#include "ShaderMaterial.hpp"
#include "../system/zTexture.hpp"

class NormalTexMaterial:public ShaderMaterial{
private:
    GLint KdLoc, KsLoc, KaLoc, ShininessLoc, lightPositionLoc, lightIntensityLoc, texloc, normalTexloc;
    GLfloat lightIntensity[3] = {0.9f, 0.9f, 0.9f};
    GLfloat Kd[3] = {0.9f, 0.9f, 0.9f};
    GLfloat Ks[3] = {0.1f, 0.1f, 0.1f};
    GLfloat Ka[3] = {0.1f, 0.1f, 0.1f};
    GLfloat Shininess = 1.0;
    glm::vec4 lightPosition;
    zTexture tex;
    zTexture normalTex;
    
public:
    NormalTexMaterial(const char* texpath, const char* normalTexpath);
    void update(glm::mat4 viewMatrix, glm::mat4 projectionMatrix) override;
};


#endif /* NormalTexMaterial_hpp */
