//
//  DirectionalLight.cpp
//  Game01
//
//  Created by kazuki sako on 2018/05/13.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#include "DirectionalLight.hpp"
#include "../renderpass/RenderPass.hpp"

DirectionalLight::DirectionalLight(glm::vec3 color, float intensity): Light(color, intensity){
    lookPos = glm::vec3(0, 0, 0);
    
    float area = 5.0f;
    projectionMatrix = glm::ortho(-1*area, area, -1*area, area, 1.0f, 100.0f);
}

void DirectionalLight::lighting(RenderPass *renderPass, int index){
    renderPass->setUniform("Light.Intensity", getIntensity());
    renderPass->setUniform("Light.Position", getPosition());
    
//    std::string before = "tests[";
//    std::string after = "].color";
//    std::string uniformName = before + std::to_string(0) + after;
//    renderPass->setUniform(uniformName.c_str(), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
}

void DirectionalLight::update(){
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    viewMatrix = glm::lookAt(position, lookPos, up);
}
