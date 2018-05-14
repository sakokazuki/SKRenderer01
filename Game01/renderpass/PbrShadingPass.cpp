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

PbrShadingPass::PbrShadingPass():RenderPass("pbrShadingPass.vert", "pbrShadingPass.frag"){
    postexloc = glGetUniformLocation(prog, "PositionTex");
    normtexloc= glGetUniformLocation(prog, "NormalTex");
    coltexloc = glGetUniformLocation(prog, "ColorTex");
    shadowtexloc = glGetUniformLocation(prog, "ShadowmapTex");
    
    quad = new QuadScreenMesh();
    
}

void PbrShadingPass::init(std::vector<Light*> l, Camera* c, std::vector<Mesh*> m){
    RenderPass::init(l, c, m);
    viewMatrix = glm::mat4(1);
    projectionMatrix = glm::mat4(1);
    
}


void PbrShadingPass::draw(){

    int directionalLightNum = 0, spotLightNum = 0, pointLightNum = 0;
    for(int i=0; i<lights.size(); i++){
        Light *light = lights[i];
        
        const std::type_info& lightType = typeid(*light);
        if(lightType == typeid(DirectionalLight)){
//            std::cout << "directonal light" << std::endl;
            lights[i]->lighting(this, directionalLightNum);
            
            directionalLightNum++;
        }else if(lightType == typeid(SpotLight)){
//            std::cout << "spot light" << std::endl;
            lights[i]->lighting(this, spotLightNum);
            spotLightNum++;
        }else{
//            std::cout << "other light" << std::endl;
            lights[i]->lighting(this, pointLightNum);
            pointLightNum++;
        }
    }

    glUniform1i(postexloc, 0);
    glUniform1i(normtexloc, 1);
    glUniform1i(coltexloc, 2);
    glUniform1i(shadowtexloc, 3);
    
    quad->draw(this);
    
    
    
    
    
}
