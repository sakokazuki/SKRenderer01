//
//  PbrShadingPass.cpp
//  Game01
//
//  Created by kazuki sako on 2018/04/30.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#include "PbrShadingPass.hpp"
#include "../lights/Light.hpp"
#include "../lights/DirectionalLight.hpp"
#include "../lights/SpotLight.hpp"
#include "../lights/PointLight.hpp"

PbrShadingPass::PbrShadingPass():RenderPass("pbrShadingPass.vert", "pbrShadingPass.frag"){
    
    quad = new QuadScreenMesh();
    
}

void PbrShadingPass::init(std::vector<Light*> l, Camera* c, std::vector<Mesh*> m){
    RenderPass::init(l, c, m);
    viewMatrix = glm::mat4(1);
    projectionMatrix = glm::mat4(1);
    
}


void PbrShadingPass::drawPass(){
    int directionalLightNum = 0, spotLightNum = 0, pointLightNum = 0;
    for(int i=0; i<lights.size(); i++){
        Light *light = lights[i];
        
        const std::type_info& lightType = typeid(*light);
        if(lightType == typeid(DirectionalLight)){
            lights[i]->lighting(this, directionalLightNum);
            directionalLightNum++;
        }else if(lightType == typeid(SpotLight)){
            lights[i]->lighting(this, spotLightNum);
            spotLightNum++;
        }else if(lightType == typeid(PointLight)){
            lights[i]->lighting(this, pointLightNum);
            pointLightNum++;
        }
    }

    setUniform("numDirectionalLights", directionalLightNum);
    setUniform("numPointLights", pointLightNum);
    setUniform("numSpotLights", spotLightNum);
    
    quad->draw(this); 
}
