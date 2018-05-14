//
//  GBufferPass.cpp
//  Game01
//
//  Created by kazuki sako on 2018/02/08.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#include "GBufferPass.hpp"
#include "../meshes/Mesh.hpp"
#include "../lights/Light.hpp"

GBufferPass::GBufferPass():RenderPass("gBufferPass.vert", "gBufferPass.frag"){
  
}

void GBufferPass::init(std::vector<Light*> l, Camera* c, std::vector<Mesh*> m){
    RenderPass::init(l, c, m);
    
}


void GBufferPass::draw(){
    viewMatrix = camera->viewMatrix;
    projectionMatrix = camera->projectionMatrix;
    
    for(int i=0; i<meshes.size(); i++){
        meshes[i]->draw(this);
    }

    


}
