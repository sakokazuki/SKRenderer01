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

    intensity = glm::vec3(0.9f, 0.9f, 0.9f);
    lightFrustum->orient(getPosition(), glm::vec3(0.0f), glm::vec3(0.0f,1.0f,0.0f));
    lightFrustum->setPerspective( 30.0f, 1.0f, 1.0f, 25.0f);
}

void Light::update(){
    lightFrustum->orient(getPosition(), glm::vec3(0.0f), glm::vec3(0.0f,1.0f,0.0f));
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
    return glm::vec4(position.x, position.y, position.z, 1.0f);
}


