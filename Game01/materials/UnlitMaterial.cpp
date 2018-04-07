//
//  UnlitMaterial.cpp
//  Game01
//
//  Created by kazuki sako on 2018/02/04.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#include "UnlitMaterial.hpp"
#include "glm/ext.hpp"


UnlitMaterial::UnlitMaterial():ShaderMaterial("unlit.vert", "unlit.frag"){

    shadowmapLoc = glGetUniformLocation(prog, "ShadowMap");
    shadowMatrixLoc = glGetUniformLocation(prog, "ShadowMatrix");
    
    tMatrix = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f));
    sMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
    rMatrix = glm::rotate(glm::mat4(), float(0), glm::vec3(1.0f, 0.0f, 0.0f));
}

void UnlitMaterial::setmvp() const{
    glm::mat4 mv = viewMatrix * tMatrix * rMatrix * sMatrix;
    glUniformMatrix4fv(modelviewloc, 1, GL_FALSE, &mv[0][0]);
    glm::mat3 normal = glm::mat3(glm::vec3(mv[0]), glm::vec3(mv[1]), glm::vec3(mv[2]));
    glUniformMatrix3fv(normalloc, 1, GL_FALSE, &normal[0][0]);
    glm::mat4 mvp = projectionMatrix * mv;
    glUniformMatrix4fv(mvploc, 1, GL_FALSE, &mvp[0][0]);
//    std::cout << glm::to_string(mvp) << std::endl;
    glUniformMatrix4fv(shadowMatrixLoc, 1, GL_FALSE, &(lightPV*tMatrix * rMatrix * sMatrix)[0][0]);
}


void UnlitMaterial::update(){
    glActiveTexture(GL_TEXTURE0);
    glUniform1i(shadowmapLoc, 0);
}
