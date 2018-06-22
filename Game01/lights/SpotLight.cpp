//
//  SpotLight.cpp
//  Game01
//
//  Created by kazuki sako on 2018/05/13.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#include "SpotLight.hpp"
#include "../renderpass/RenderPass.hpp"
#include <fmt/format.h>


SpotLight::SpotLight(glm::vec3 color, float intensity, float distance, float angle, float penumbra, float decay): Light(color, intensity){
    lookPos = glm::vec3(0, 0, 0);    
    projectionMatrix = glm::perspective(glm::radians(angle), 1.0f, 1.0f, 1000.0f);
    this->angle = angle;
    this->distance = distance;
    this->penumbra = penumbra;
    this->decay = decay;
}

void SpotLight::lighting(RenderPass *renderPass, int index){

    
    std::string name = fmt::format("{0}[{1}].{2}", "SpotLights", index, "position");
    glm::vec3 lightPos = renderPass->camera->viewMatrix * glm::vec4(position, 1.0f);
    renderPass->setUniform(name.c_str(), lightPos);
    
    name = fmt::format("{0}[{1}].{2}", "SpotLights", index, "direction");
    glm::vec4 lightDir = glm::vec4(glm::normalize(position - lookPos), 0);
    glm::vec3 direction = renderPass->camera->viewMatrix*lightDir;
    renderPass->setUniform(name.c_str(), direction);
    
    name = fmt::format("{0}[{1}].{2}", "SpotLights", index, "color");
    renderPass->setUniform(name.c_str(), getIntensity());
    
    name = fmt::format("{0}[{1}].{2}", "SpotLights", index, "distance");
    renderPass->setUniform(name.c_str(), distance);
    
    name = fmt::format("{0}[{1}].{2}", "SpotLights", index, "decay");
    renderPass->setUniform(name.c_str(), decay);
    
    name = fmt::format("{0}[{1}].{2}", "SpotLights", index, "coneCos");
    renderPass->setUniform(name.c_str(), glm::cos(glm::radians(angle)));
    
    name = fmt::format("{0}[{1}].{2}", "SpotLights", index, "penumbraCos");
    renderPass->setUniform(name.c_str(), glm::cos(glm::radians(angle) * (1.0f - penumbra)));
    
//    std::cout << "--------------=" << std::endl;
//    std::cout << lightPos.x << ",  " << lightPos.y << ", " << lightPos.z << ", "<< w << std::endl;
//    std::cout << "lightposition: " << glm::to_string(position) << std::endl;
//    std::cout << "viewMatrix: " << glm::to_string(renderPass->camera->viewMatrix) << std::endl;
//    std::cout << "direction : " << glm::to_string(direction) << std::endl;
//    std::cout << "distance: " << distance << std::endl;
//    std::cout << "coneCos: " << glm::cos(glm::radians(angle)) << std::endl;
}

void SpotLight::update(){
    Object3D::update();
    
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    viewMatrix = glm::lookAt(position, lookPos, up);
    
    
}
