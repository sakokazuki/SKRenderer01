//
//  3DObject.cpp
//  Game01
//
//  Created by kazuki sako on 2018/02/07.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#include "3DObject.hpp"



_3DObject::_3DObject(){
    position = glm::vec3(0.0f, 0.0f, 0.0f);
    tMatrix = glm::translate(glm::mat4(), position);
    scale = glm::vec3(1.0f);
    sMatrix = glm::scale(glm::mat4(1.0f), scale);
    rMatrix = glm::rotate(glm::mat4(), float(0), glm::vec3(1.0f, 0.0f, 0.0f));
}

void _3DObject::setTranslate(float x, float y, float z){
//    std::cout << x << ", " << y << ", " << z << std::endl;
    position = glm::vec3(x, y, z);
    tMatrix = glm::translate(glm::mat4(), position);
}


void _3DObject::setRotate(float angle, glm::vec3 dir){
    rMatrix = glm::rotate(glm::mat4(), angle, dir);
}
void _3DObject::setScale(float x, float y, float z){
    scale = glm::vec3(x, y, z);
    sMatrix =  glm::scale(glm::mat4(1.0f), scale);
}


glm::mat4 _3DObject::getModelMatrix() const{
    return tMatrix * rMatrix * sMatrix;
}

