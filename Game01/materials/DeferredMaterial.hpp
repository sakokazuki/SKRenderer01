//
//  DeferrdMaterial.hpp
//  Game01
//
//  Created by kazuki sako on 2018/01/25.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#ifndef DeferrdMaterial_hpp
#define DeferrdMaterial_hpp

#include <stdio.h>

#include "ShaderMaterial.hpp"
#include "../system/zTexture.hpp"

class DeferredMaterial:public ShaderMaterial{
private:
    GLint KdLoc, ShininessLoc, lightPositionLoc, lightIntensityLoc, postexloc, normtexloc, coltexloc;
    GLfloat lightIntensity[3] = {0.9f, 0.9f, 0.9f};
    GLfloat Kd[3] = {0.9f, 0.9f, 0.9f};
    GLfloat Shininess = 1.0;
    glm::vec4 lightPosition;
    GLuint pass1Index, pass2Index;
    
public:
    DeferredMaterial();

    void update(int passindex, glm::mat4 viewMatrix, glm::mat4 projectionMatrix);
};


#endif /* DeferrdMaterial_hpp */
