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
#include "../lights/Light.hpp"

ShadowmapPass::ShadowmapPass():RenderPass("unlit.vert", "unlit.frag"){
    shadowMatrixLoc = glGetUniformLocation(prog, "ShadowMatrix");
    
//    tMatrix = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f));
//    sMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
//    rMatrix = glm::rotate(glm::mat4(), float(0), glm::vec3(1.0f, 0.0f, 0.0f));
}

void ShadowmapPass::init(std::vector<Light*> l, Camera* c, std::vector<Mesh*> m){
    RenderPass::init(l, c, m);
    viewMatrix = camera->viewMatrix;
    projectionMatrix = camera->projectionMatrix;
}


void ShadowmapPass::draw(){
    
    //シャドウマップ生成に使うライトは1つだけ。castshadow=trueにしたものにする。
    Light *light = lights[0];
    for(int i=0; i<lights.size(); i++){
        if(lights[i]->castShadow == true){
            light = lights[i];
            break;
        }
    }
    
    for(int i=0; i<meshes.size(); i++){

        glUniformMatrix4fv(shadowMatrixLoc, 1, GL_FALSE, &(light->getPVMatrix() * meshes[i]->getModelMatrix())[0][0]);
        meshes[i]->draw(this);
    }    
}

