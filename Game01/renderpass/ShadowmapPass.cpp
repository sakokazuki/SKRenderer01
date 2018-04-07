//
//  ShadowmapPass.cpp
//  Game01
//
//  Created by kazuki sako on 2018/02/07.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#include "ShadowmapPass.hpp"
#include "glm/ext.hpp"
#include "../meshes/Mesh.hpp"

ShadowmapPass::ShadowmapPass():RenderPass("unlit.vert", "unlit.frag"){
    shadowMatrixLoc = glGetUniformLocation(prog, "ShadowMatrix");
    
//    tMatrix = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f));
//    sMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
//    rMatrix = glm::rotate(glm::mat4(), float(0), glm::vec3(1.0f, 0.0f, 0.0f));
}

void ShadowmapPass::init(Light *l, Camera *c, std::vector<Mesh *> m){
    RenderPass::init(l, c, m);
    viewMatrix = camera->viewMatrix;
    projectionMatrix = camera->projectionMatrix;
}


void ShadowmapPass::draw(){
    
    for(int i=0; i<meshes.size(); i++){
//        glm::mat4 mv = viewMatrix * meshes[i]->getModelMatrix();
//        glUniformMatrix4fv(modelviewloc, 1, GL_FALSE, &mv[0][0]);
//        glm::mat3 normal = glm::mat3(glm::vec3(mv[0]), glm::vec3(mv[1]), glm::vec3(mv[2]));
//        glUniformMatrix3fv(normalloc, 1, GL_FALSE, &normal[0][0]);
//        glm::mat4 mvp = projectionMatrix * mv;
//        glUniformMatrix4fv(mvploc, 1, GL_FALSE, &mvp[0][0]);
        glUniformMatrix4fv(shadowMatrixLoc, 1, GL_FALSE, &(light->getPVMatrix() * meshes[i]->getModelMatrix())[0][0]);
        meshes[i]->draw(this);
    }    
}

