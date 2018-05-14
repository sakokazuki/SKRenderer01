//
//  SpotLight.cpp
//  Game01
//
//  Created by kazuki sako on 2018/05/13.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#include "SpotLight.hpp"
#include "../renderpass/RenderPass.hpp"

SpotLight::SpotLight(glm::vec3 color, float intensity, float distance, float angle, float penumbra, float decay): Light(color, intensity){
    lookPos = glm::vec3(0, 0, 0);    
    projectionMatrix = glm::perspective(glm::radians(angle), 1.0f, 1.0f, 1000.0f);
}

void SpotLight::lighting(RenderPass *renderPass, int index){
    renderPass->setUniform("Light.Intensity", getIntensity());
    renderPass->setUniform("Light.Position", getPosition());
    
//    std::string before = "tests[";
//    std::string after = "].color";
//    std::string uniformName = before + std::to_string(1) + after;
//    renderPass->setUniform(uniformName.c_str(), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
    
    
    
}

void SpotLight::update(){
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    viewMatrix = glm::lookAt(position, lookPos, up);
}
