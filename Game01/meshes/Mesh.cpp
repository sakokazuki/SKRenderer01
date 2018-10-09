//
//  Mesh.cpp
//  Game01
//
//  Created by kazuki sako on 2018/02/07.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#include "Mesh.hpp"
#include "../renderpass/RenderPass.hpp"
#include "glm/gtx/string_cast.hpp"

Mesh::Mesh():Object3D(){
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    meshMaterial = new MeshMaterial();
}

void Mesh::draw() const{
}

void Mesh::draw(RenderPass *renderPass) const{
    meshMaterial->setUniforms(renderPass);
    
    glm::mat4 mv = renderPass->viewMatrix * getModelMatrix();
    glUniformMatrix4fv(renderPass->modelviewloc, 1, GL_FALSE, &mv[0][0]);
    glm::mat3 normal = glm::mat3(glm::vec3(mv[0]), glm::vec3(mv[1]), glm::vec3(mv[2]));
    glUniformMatrix3fv(renderPass->normalloc, 1, GL_FALSE, &normal[0][0]);
    glm::mat4 mvp = renderPass->projectionMatrix * mv;
    glUniformMatrix4fv(renderPass->mvploc, 1, GL_FALSE, &mvp[0][0]);


	draw();

}


Mesh::~Mesh(){
}
