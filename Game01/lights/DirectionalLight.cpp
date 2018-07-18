//
//  DirectionalLight.cpp
//  Game01
//
//  Created by kazuki sako on 2018/05/13.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#include "DirectionalLight.hpp"
#include "../renderpass/RenderPass.hpp"
#include <fmt/format.h>

DirectionalLight::DirectionalLight(glm::vec3 color, float intensity): Light(color, intensity){
    lookPos = glm::vec3(0, 0, 0);
    
    float area = 5.0f;
    projectionMatrix = glm::ortho(-1*area, area, -1*area, area, 1.0f, 100.0f);
}

void DirectionalLight::lighting(RenderPass *renderPass, int index){
    
    std::string name = fmt::format("{0}[{1}].{2}", "DirectionalLights", index, "direction");
    glm::vec4 lightDir = glm::vec4(glm::normalize(Object3D::getPosition() - lookPos), 0);
    glm::vec3 direction = renderPass->camera->viewMatrix*lightDir;
    renderPass->setUniform(name.c_str(), direction);
    
    name = fmt::format("{0}[{1}].{2}", "DirectionalLights", index, "color");
    renderPass->setUniform(name.c_str(), getIntensity());
}

void DirectionalLight::update(){
    Object3D::update();
    
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    viewMatrix = glm::lookAt(Object3D::getPosition(), lookPos, up);
    
    
}
