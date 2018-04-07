//
//  PhongMat.hpp
//  Game01
//
//  Created by kazuki sako on 2018/01/24.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#ifndef PhongMat_hpp
#define PhongMat_hpp

#include <stdio.h>
#include "ShaderMaterial.hpp"

class PhongMaterial:public ShaderMaterial{
private:
    GLint KdLoc, KsLoc, KaLoc, ShininessLoc, lightPositionLoc, lightIntensityLoc;
    GLfloat lightIntensity[3] = {0.9f, 0.9f, 0.9f};
    GLfloat Kd[3] = {0.9f, 0.9f, 0.9f};
    GLfloat Ks[3] = {0.1f, 0.1f, 0.1f};
    GLfloat Ka[3] = {0.1f, 0.1f, 0.1f};
    GLfloat Shininess = 1.0;
    glm::vec4 lightPosition;
public:
    PhongMaterial();
    void update(glm::mat4 viewMatrix, glm::mat4 projectionMatrix) override;
};


#endif /* PhongMat_hpp */
