//
//  PointLight.cpp
//  Game01
//
//  Created by kazuki sako on 2018/05/15.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#include "PointLight.hpp"
#include "../renderpass/RenderPass.hpp"
#include <fmt/format.h>

PointLight::PointLight(glm::vec3 color, float intensity, float distance, float decay): Light(color, intensity){
    //point lihgtは影に使うmatrix関連は適当のまま
    projectionMatrix = glm::mat4(0.0);
    this->distance = distance;
    this->decay = decay;
}

void PointLight::lighting(RenderPass *renderPass, int index){
    renderPass->setUniform("Light.Intensity", getIntensity());
    renderPass->setUniform("Light.Position", getPosition());
    
    std::string name = fmt::format("{0}[{1}].{2}", "PointLights", index, "position");
    glm::vec3 lightPos = renderPass->camera->viewMatrix * glm::vec4(position, 1.0f);
    renderPass->setUniform(name.c_str(), lightPos);

    name = fmt::format("{0}[{1}].{2}", "PointLights", index, "color");
    renderPass->setUniform(name.c_str(), getIntensity());

    name = fmt::format("{0}[{1}].{2}", "PointLights", index, "distance");
    renderPass->setUniform(name.c_str(), distance);

    name = fmt::format("{0}[{1}].{2}", "PointLights", index, "decay");
    renderPass->setUniform(name.c_str(), decay);    
}

void PointLight::update(){
    //point lihgtは影に使うmatrix関連は適当のまま
    viewMatrix = glm::mat4(0.0);
}
