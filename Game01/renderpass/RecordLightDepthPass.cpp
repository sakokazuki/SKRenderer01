//
//  RecordLightDepthPass.cpp
//  Game01
//
//  Created by kazuki sako on 2018/02/08.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#include "RecordLightDepthPass.hpp"
#include "../meshes/Mesh.hpp"

RecordLightDepthPass::RecordLightDepthPass():RenderPass("recordLightDepthPass.vert", "recordLightDepthPass.frag"){

}

void RecordLightDepthPass::init(Light *l, Camera *c, std::vector<Mesh *> m){
    RenderPass::init(l, c, m);
    viewMatrix = light->getViewMatrix();
    projectionMatrix = light->getProjectionMatrix();
    
}


void RecordLightDepthPass::draw(){
    for(int i=0; i<meshes.size(); i++){
//        glm::mat4 mv = viewMatrix * meshes[i]->getModelMatrix();
//        glUniformMatrix4fv(modelviewloc, 1, GL_FALSE, &mv[0][0]);
//        glm::mat3 normal = glm::mat3(glm::vec3(mv[0]), glm::vec3(mv[1]), glm::vec3(mv[2]));
//        glUniformMatrix3fv(normalloc, 1, GL_FALSE, &normal[0][0]);
//        glm::mat4 mvp = projectionMatrix * mv;
//        glUniformMatrix4fv(mvploc, 1, GL_FALSE, &mvp[0][0]);
        meshes[i]->draw(this);
    }
}
