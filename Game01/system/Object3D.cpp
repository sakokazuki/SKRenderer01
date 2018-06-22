//
//  Object3D.cpp
//  Game01
//
//  Created by kazuki sako on 2018/02/07.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#include "Object3D.hpp"


Object3D::Object3D():
    rotation(glm::vec3(0)),
    quaternion(glm::quat(0, 0, 0, 1)),
    position(glm::vec3(0)),
    scale(glm::vec3(1))
{
    
    tMatrix = glm::translate(glm::mat4(), position);
    sMatrix = glm::scale(glm::mat4(1.0f), scale);
    rMatrix = glm::rotate(glm::mat4(), float(0), glm::vec3(1.0f, 0.0f, 0.0f));
}

char* Object3D::classname(){
    int a;
    return abi::__cxa_demangle(typeid(*this).name(), 0, 0, &a );
}

void Object3D::update(){
}

void Object3D::setTranslate(float x, float y, float z){
    position = glm::vec3(x, y, z);
    tMatrix = glm::translate(glm::mat4(), position);
}

glm::vec3 Object3D::getPosition() const {
    return position;
}

void Object3D::setScale(float x, float y, float z){
    scale = glm::vec3(x, y, z);
    sMatrix =  glm::scale(glm::mat4(1.0f), scale);
}

glm::vec3 Object3D::getScale() const {
    return scale;
}


void Object3D::setAngleAxis(float angle, glm::vec3 axis){
    glm::quat q = glm::angleAxis(glm::radians(angle), glm::normalize(axis));
    setQuaternion(q);
}

void Object3D::setQuaternion(glm::quat q){
    quaternion = q;
    onChangeQuaternion();
    updateRMatrix();
}

void Object3D::setRotation(glm::vec3 r){
    rotation = r;
    onChangeRotation();
    updateRMatrix();
}

void Object3D::onChangeRotation(){
    quaternion = glm::quat(rotation * 2.0f * M_PI / 360.0f);
}

void Object3D::onChangeQuaternion(){
    glm::vec3 eulerAngle = glm::eulerAngles(quaternion) * 360.0f / (M_PI * 2.0f);
    rotation = eulerAngle;
}

void Object3D::updateRMatrix(){
    rMatrix = glm::toMat4(quaternion);
}


glm::vec3 Object3D::getEulerAnlge() const{
    return rotation;
}

glm::quat Object3D::getQuaternion() const{
    return quaternion;
}

glm::mat4 Object3D::getModelMatrix() const{
    return tMatrix * rMatrix * sMatrix;
}








