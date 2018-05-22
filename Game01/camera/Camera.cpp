//
//  Camera.cpp
//  Game01
//
//  Created by kazuki sako on 2018/02/07.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#include "Camera.hpp"

Camera::Camera(int w, int h){
    
    lookPos = glm::vec3(0.0f, 0.0f, 0.0f);
    viewMatrix = glm::lookAt(position, lookPos, glm::vec3(0.0f, 1.0f, 0.0f));
    width = w;
    height = h;
    
    
}

void Camera::update(){
    viewMatrix = glm::lookAt(position, lookPos, glm::vec3(0.0f, 1.0f, 0.0f));
    const float fovy = 100.0 * 0.01f;
    const float aspect = (float)width / height;
    projectionMatrix = glm::perspective(fovy, aspect, 1.0f, 100.0f);
}


