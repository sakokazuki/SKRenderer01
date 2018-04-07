//
//  ShaderMaterial.cpp
//  Game01
//
//  Created by kazuki sako on 2018/01/24.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#include "ShaderMaterial.hpp"

ShaderMaterial::ShaderMaterial(std::string vert, std::string frag): shadername_vert(vert), shadername_frag(frag){
    complieShader();
    
    modelviewloc = glGetUniformLocation(prog, "ModelViewMatrix");
    mvploc = glGetUniformLocation(prog, "MVP");
    normalloc = glGetUniformLocation(prog, "NormalMatrix");
    
    tMatrix = glm::mat4(1.0);
    sMatrix = glm::mat4(1.0);
    rMatrix = glm::mat4(1.0);
}

void ShaderMaterial::update(glm::mat4 viewMatrix, glm::mat4 projectionMatrix){
    glm::mat4 mv = viewMatrix * tMatrix * rMatrix * sMatrix;
    glUniformMatrix4fv(modelviewloc, 1, GL_FALSE, &mv[0][0]);
    glm::mat3 normal = glm::mat3(glm::vec3(mv[0]), glm::vec3(mv[1]), glm::vec3(mv[2]));
    glUniformMatrix3fv(normalloc, 1, GL_FALSE, &normal[0][0]);
    glm::mat4 mvp = projectionMatrix * mv;
    glUniformMatrix4fv(mvploc, 1, GL_FALSE, &mvp[0][0]);
    
}

void ShaderMaterial::complieShader(){
    GLuint frag, vert;
    if(!CreateCompileShader(shadername_vert, GL_VERTEX_SHADER, vert)){
        throw "vertexshader compile error";
    }
    if(!CreateCompileShader(shadername_frag, GL_FRAGMENT_SHADER, frag)){
        throw "fragmentshader compile error";
    }
    prog = LinkShader(vert, frag);
}

