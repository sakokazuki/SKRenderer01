//
//  Light.cpp
//  Game01
//
//  Created by kazuki sako on 2018/02/03.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#include "Light.hpp"
#include "../renderpass/RenderPass.hpp"

Light::Light(glm::vec3 color, float intensity): castShadow(false), enable(true){
    shadowBias = glm::mat4(glm::vec4(0.5f,0.0f,0.0f,0.0f),
                           glm::vec4(0.0f,0.5f,0.0f,0.0f),
                           glm::vec4(0.0f,0.0f,0.5f,0.0f),
                           glm::vec4(0.5f,0.5f,0.5f,1.0f)
                           );
    
    this->color = color;
    this->intensity = intensity;

}


void Light::lighting(RenderPass *renderPass, int index){
    renderPass->setUniform("Light.Intensity", getIntensity());
    renderPass->setUniform("Light.Position", getPosition());
}


glm::vec3 Light::getIntensity() const{
    return intensity * color;
}

glm::mat4 Light::getProjectionMatrix() const{
    return projectionMatrix;
}

glm::mat4 Light::getViewMatrix() const{
    return viewMatrix;
}

glm::mat4 Light::getPVMatrix() const{
    return shadowBias * getProjectionMatrix() * getViewMatrix();
}

glm::vec4 Light::getPosition() const{
    return glm::vec4(position.x, position.y, position.z, 1.0f);
}


