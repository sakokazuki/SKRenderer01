//
//  PbrShadingPass.cpp
//  Game01
//
//  Created by kazuki sako on 2018/04/30.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#include "PbrShadingPass.hpp"

PbrShadingPass::PbrShadingPass():RenderPass("pbrShadingPass.vert", "pbrShadingPass.frag"){
    postexloc = glGetUniformLocation(prog, "PositionTex");
    normtexloc= glGetUniformLocation(prog, "NormalTex");
    coltexloc = glGetUniformLocation(prog, "ColorTex");
    shadowtexloc = glGetUniformLocation(prog, "ShadowmapTex");
    
    quad = new QuadScreenMesh();
    
}

void PbrShadingPass::init(Light *l, Camera *c, std::vector<Mesh *> m){
    RenderPass::init(l, c, m);
    viewMatrix = glm::mat4(1);
    projectionMatrix = glm::mat4(1);
    
}


void PbrShadingPass::draw(){
    setUniform("Light.Intensity", light->getIntensity());
    setUniform("Light.Position", light->getPosition());
    
    //    glm::mat4 mv = viewMatrix * quad->getModelMatrix();
    //    glUniformMatrix4fv(modelviewloc, 1, GL_FALSE, &mv[0][0]);
    //    glm::mat3 normal = glm::mat3(glm::vec3(mv[0]), glm::vec3(mv[1]), glm::vec3(mv[2]));
    //    glUniformMatrix3fv(normalloc, 1, GL_FALSE, &normal[0][0]);
    //    glm::mat4 mvp = projectionMatrix * mv;
    //    glUniformMatrix4fv(mvploc, 1, GL_FALSE, &mvp[0][0]);
    
    glUniform1i(postexloc, 0);
    glUniform1i(normtexloc, 1);
    glUniform1i(coltexloc, 2);
    glUniform1i(shadowtexloc, 3);
    
    quad->draw(this);
    
    
    
    
    
}
