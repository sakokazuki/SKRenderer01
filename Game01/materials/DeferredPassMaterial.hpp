//
//  DeferredPassMaterial.hpp
//  Game01
//
//  Created by kazuki sako on 2018/02/04.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#ifndef DeferredPassMaterial_hpp
#define DeferredPassMaterial_hpp

#include <stdio.h>
#include "ShaderMaterial.hpp"
#include "../system/zTexture.hpp"
class DeferredPassMaterial{
private:
    void complieShader();
    const std::string shadername_vert;
    const std::string shadername_frag;
    GLint model, view, projection;
    GLint mvploc, modelviewloc, normalloc;
    
    GLint KdLoc, ShininessLoc, lightPositionLoc, lightIntensityLoc, postexloc, normtexloc, coltexloc, shadowtexloc;
    const glm::vec3 lihgtIntensity = glm::vec3(0.9f, 0.9f, 0.9f);
    const glm::vec3 Kd = glm::vec3(0.9f, 0.9f, 0.9f);
    GLfloat Shininess = 1.0;
    glm::vec4 lightPosition;
    GLuint pass1Index, pass2Index;
    
public:
    DeferredPassMaterial();
    GLuint prog;
    glm::mat4 tMatrix, sMatrix, rMatrix, viewMatrix, projectionMatrix;
    
    void pass1();
    void pass2();
    void setUniform(const char* name, glm::vec3 data) const;
    void setUniform(const char* name, glm::vec4 data) const;
    void setUniform(const char* name, glm::mat4 data) const;
    void setUniform(const char* name, float data) const;
    void setmvp() const;
};




#endif /* DeferredPassMaterial_hpp */




