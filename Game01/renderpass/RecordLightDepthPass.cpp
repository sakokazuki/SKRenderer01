//
//  RecordLightDepthPass.cpp
//  Game01
//
//  Created by kazuki sako on 2018/02/08.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#include "RecordLightDepthPass.hpp"
#include "../meshes/Mesh.hpp"
#include "../lights/Light.hpp"

RecordLightDepthPass::RecordLightDepthPass():RenderPass("recordLightDepthPass.vert", "recordLightDepthPass.frag"){

}

void RecordLightDepthPass::init(std::vector<Light*> l, Camera* c, std::vector<Mesh*> m){
    RenderPass::init(l, c, m);
    
    
}


void RecordLightDepthPass::draw(){
    
    //シャドウマップ生成に使うライトは1つだけ。castshadow=trueにしたものにする。
    Light *light = lights[0];
    for(int i=0; i<lights.size(); i++){
        if(lights[i]->castShadow == true){
            light = lights[i];
            break;
        }
    }
    viewMatrix = light->getViewMatrix();
    projectionMatrix = light->getProjectionMatrix();
    
    for(int i=0; i<meshes.size(); i++){

        meshes[i]->draw(this);
    }
}
