//
//  ShaderMaterial.hpp
//  Game01
//
//  Created by kazuki sako on 2018/01/24.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#ifndef ShaderMaterial_hpp
#define ShaderMaterial_hpp

#include <stdio.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <GL/glew.h>
#include "../system/ShaderFunc.hpp"

class ShaderMaterial{
private:
    void complieShader();
protected:
    const std::string shadername_vert;
    const std::string shadername_frag;
    GLint model, view, projection;
    GLint mvploc, modelviewloc, normalloc;


public:
    GLuint prog;
    glm::mat4 tMatrix, sMatrix, rMatrix;
    ShaderMaterial(std::string vert, std::string frag);
    virtual void update(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);
};

#endif /* ShaderMaterial_hpp */

