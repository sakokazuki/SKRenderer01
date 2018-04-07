//
//  ShadowmapPassMaterial.hpp
//  Game01
//
//  Created by kazuki sako on 2018/02/03.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#ifndef ShadowmapPassMaterial_hpp
#define ShadowmapPassMaterial_hpp

#include <stdio.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <GL/glew.h>
#include "../system/ShaderFunc.hpp"
#include "../system/frustum.h"

class ShadowmapPassMaterial{
private:
    void complieShader();
    const std::string shadername_vert;
    const std::string shadername_frag;
    GLint model, view, projection;
    GLint mvploc, modelviewloc, normalloc;
    GLint shadowmapLoc, shadowMatrixLoc;
    GLuint pass1Index, pass2Index;
        
public:
    GLuint prog;
    glm::mat4 tMatrix, sMatrix, rMatrix, viewMatrix, projectionMatrix;
    ShadowmapPassMaterial();
    mat4 lightPV;
    void setmvp() const;
    void pass1();
    void pass2();
};


#endif /* ShadowmapPassMaterial_hpp */
