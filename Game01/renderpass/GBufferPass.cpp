//
//  GBufferPass.cpp
//  Game01
//
//  Created by kazuki sako on 2018/02/08.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#include "GBufferPass.hpp"
#include "../meshes/Mesh.hpp"

GBufferPass::GBufferPass():RenderPass("gBufferPass.vert", "gBufferPass.frag"){
  
}

void GBufferPass::init(Light *l, Camera *c, std::vector<Mesh *> m){
    RenderPass::init(l, c, m);
    viewMatrix = camera->viewMatrix;
    projectionMatrix = camera->projectionMatrix;
}


void GBufferPass::draw(){
    setUniform("Material.Kd", glm::vec3(1.0f, 1.0f, 1.0f));
    
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
