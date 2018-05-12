//
//  SpotLight.cpp
//  Game01
//
//  Created by kazuki sako on 2018/05/13.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#include "SpotLight.hpp"

SpotLight::SpotLight(glm::vec3 color, float intensity, float distance, float angle, float penumbra, float decay): Light(color, intensity){
//    projectionMatrix = glm::perspective(angle, 1.0f, 0.1f, distance);
    lookPos = glm::vec3(0, 0, 0);
    
    lightFrustum = new Frustum(Projection::PERSPECTIVE);
    lightFrustum->orient(getPosition(), glm::vec3(0.0f), glm::vec3(0.0f,1.0f,0.0f));
    lightFrustum->setPerspective( 30.0f, 1.0f, 1.0f, 25.0f);
}

glm::vec4 SpotLight::getPosition(){
    return glm::vec4(position.x, position.y, position.z, 1.0f);
}

void SpotLight::update(){
//    std::cout << "light update" << std::endl;
//    lightFrustum->orient(getPosition(), glm::vec3(0.0f), glm::vec3(0.0f,1.0f,0.0f));
//    viewMatrix = lightFrustum->getViewMatrix();
//    projectionMatrix = lightFrustum->getProjectionMatrix();
    
    
//    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
//    viewMatrix = glm::lookAt(position, lookPos, up);
}
