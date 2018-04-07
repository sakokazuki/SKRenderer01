//
//  ShadowmapPassMaterial.cpp
//  Game01
//
//  Created by kazuki sako on 2018/02/03.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#include "ShadowmapPassMaterial.hpp"

ShadowmapPassMaterial::ShadowmapPassMaterial(): shadername_vert("shadowmappass.vert"), shadername_frag("shadowmappass.frag"){
    complieShader();
    
    modelviewloc = glGetUniformLocation(prog, "ModelViewMatrix");
    mvploc = glGetUniformLocation(prog, "MVP");
    normalloc = glGetUniformLocation(prog, "NormalMatrix");
    shadowmapLoc = glGetUniformLocation(prog, "ShadowMap");
    shadowMatrixLoc = glGetUniformLocation(prog, "ShadowMatrix");
    

    
    tMatrix = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f));
    sMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
    rMatrix = glm::rotate(glm::mat4(), float(0), glm::vec3(1.0f, 0.0f, 0.0f));
    
    pass1Index = glGetSubroutineIndex( prog, GL_FRAGMENT_SHADER, "recordDepth");
    pass2Index = glGetSubroutineIndex( prog, GL_FRAGMENT_SHADER, "shadeWithShadow");

}


void ShadowmapPassMaterial::setmvp() const{
    glm::mat4 mv = viewMatrix * tMatrix * rMatrix * sMatrix;
    glUniformMatrix4fv(modelviewloc, 1, GL_FALSE, &mv[0][0]);
    glm::mat3 normal = glm::mat3(glm::vec3(mv[0]), glm::vec3(mv[1]), glm::vec3(mv[2]));
    glUniformMatrix3fv(normalloc, 1, GL_FALSE, &normal[0][0]);
    glm::mat4 mvp = projectionMatrix * mv;
    glUniformMatrix4fv(mvploc, 1, GL_FALSE, &mvp[0][0]);
    
    glUniformMatrix4fv(shadowMatrixLoc, 1, GL_FALSE, &(lightPV*tMatrix * rMatrix * sMatrix)[0][0]);
}


void ShadowmapPassMaterial::pass1(){
    glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &pass1Index);
}

void ShadowmapPassMaterial::pass2(){
    glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &pass2Index);
    glActiveTexture(GL_TEXTURE0);
    glUniform1i(shadowmapLoc, 0);
}



void ShadowmapPassMaterial::complieShader(){
    GLuint frag, vert;
    if(!CreateCompileShader(shadername_vert, GL_VERTEX_SHADER, vert)){
        throw "vertexshader compile error";
    }
    if(!CreateCompileShader(shadername_frag, GL_FRAGMENT_SHADER, frag)){
        throw "fragmentshader compile error";
    }
    prog = LinkShader(vert, frag);
}
