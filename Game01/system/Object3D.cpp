//
//  Object3D.cpp
//  Game01
//
//  Created by kazuki sako on 2018/02/07.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#include "Object3D.hpp"
#include "Object3DBehaviour.hpp"



Object3D::Object3D()
{
    tMatrix = glm::translate(glm::mat4(), glm::vec3(0));
    sMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1));
    rMatrix = glm::rotate(glm::mat4(), float(0), glm::vec3(1.0f, 0.0f, 0.0f));
    p_tMatrix = &tMatrix;
    p_sMatrix = &sMatrix;
    p_rMatrix = &rMatrix;
}

char* Object3D::classname(){
    int n;
    return abi::__cxa_demangle(typeid(*this).name(), 0, 0, &n);
}

void Object3D::update(){
    for(int i=0; i<behaviours.size(); i++){
        behaviours[i]->update();
    }
    for(int i=0; i<children.size(); i++){
        children[i]->update();
    }
}

void Object3D::setTranslate(float x, float y, float z){
    *p_tMatrix = glm::translate(glm::mat4(), glm::vec3(x, y, z));
}

glm::vec3 Object3D::getPosition() const {
    glm::mat4 tMat = *p_tMatrix;
    return glm::vec3(tMat[3][0], tMat[3][1], tMat[3][2]);
}

void Object3D::setScale(float x, float y, float z){
    *p_sMatrix =  glm::scale(glm::mat4(1.0f), glm::vec3(x, y, z));
}

glm::vec3 Object3D::getScale() const {
    glm::mat4 sMat = *p_sMatrix;
    return glm::vec3(sMat[0][0], sMat[1][1], sMat[2][2]);
}


void Object3D::setAngleAxis(float angle, glm::vec3 axis){
    glm::quat q = glm::angleAxis(glm::radians(angle), glm::normalize(axis));
    *p_rMatrix = glm::toMat4(q);
}

void Object3D::setQuaternion(glm::quat q){
    *p_rMatrix = glm::toMat4(q);
}

void Object3D::setRotation(glm::vec3 r){
    glm::quat q = glm::quat(r * 2.0f * M_PI / 360.0f);
    *p_rMatrix = glm::toMat4(q);
}

glm::vec3 Object3D::getEulerAnlge() const{
    glm::quat q = getQuaternion();
    glm::vec3 eulerAngle = glm::eulerAngles(q) * 360.0f / (M_PI * 2.0f);
    return eulerAngle;
}

glm::quat Object3D::getQuaternion() const{
    return glm::quat(*p_rMatrix);
}

glm::mat4 Object3D::getModelMatrix() const{
    return *p_tMatrix * *p_rMatrix * *p_sMatrix;
}

void Object3D::addChildren(Object3D *object){
    children.push_back(object);
}

void Object3D::addBheaviour(Object3DBehaviour *behaviour){
    behaviour->p_tMatrix = p_tMatrix;
    behaviour->p_sMatrix = p_sMatrix;
    behaviour->p_rMatrix = p_rMatrix;
    behaviours.push_back(behaviour);
}








