//
//  Light.cpp
//  Game01
//
//  Created by kazuki sako on 2018/02/03.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#include "Light.hpp"

Light::Light(){
    shadowBias = glm::mat4(glm::vec4(0.5f,0.0f,0.0f,0.0f),
                           glm::vec4(0.0f,0.5f,0.0f,0.0f),
                           glm::vec4(0.0f,0.0f,0.5f,0.0f),
                           glm::vec4(0.5f,0.5f,0.5f,1.0f)
                           );
    lightFrustum = new Frustum(Projection::PERSPECTIVE);
    float angle = 0.957283;
    
    position = glm::vec4(10.0f * cos(angle), 3.0f, 10.0f * sin(angle), 1.0f);
    intensity = glm::vec3(0.9f, 0.9f, 0.9f);
    lightFrustum->orient(position, glm::vec3(0.0f), glm::vec3(0.0f,1.0f,0.0f));
    lightFrustum->setPerspective( 50.0f, 1.0f, 1.0f, 25.0f);
}

glm::vec3 Light::getIntensity() const{
    return intensity;
}

glm::mat4 Light::getProjectionMatrix() const{
    return lightFrustum->getProjectionMatrix();
}

glm::mat4 Light::getViewMatrix() const{
    return lightFrustum->getViewMatrix();
}

glm::mat4 Light::getPVMatrix() const{
    return shadowBias * getProjectionMatrix() * getViewMatrix();
}

glm::vec4 Light::getPosition() const{
    return position;
}


