//
//  Object3D.cpp
//  Game01
//
//  Created by kazuki sako on 2018/02/07.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#include "Object3D.hpp"
#include "Object3DBehaviour.hpp"
#include "../renderpass/RenderPass.hpp"



Object3D::Object3D()
{
    tMatrix = glm::translate(glm::mat4(1), glm::vec3(0));
    sMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1));
    rMatrix = glm::rotate(glm::mat4(1), float(0), glm::vec3(1.0f, 0.0f, 0.0f));

    p_tMatrix = &tMatrix;
    p_sMatrix = &sMatrix;
    p_rMatrix = &rMatrix;
    parent = nullptr;
    isDebug = false;
}

char* Object3D::classname(){
    /*int n;
    return abi::__cxa_demangle(typeid(*this).name(), 0, 0, &n);*/
	char n = 'n';
	return &n;
}

void Object3D::update(){
    for(int i=0; i<behaviours.size(); i++){
        behaviours[i]->update();
    }
    
    for(int i=0; i<children.size(); i++){
        auto child = children[i];
        child->update();
    }
}


void Object3D::updateParent(Object3D *object){
    parent = object;

    for(int i=0; i<children.size(); i++){
        children[i]->updateParent(this);
    }
}

void Object3D::draw(RenderPass *renderPass) const{
    for(int i=0; i<children.size(); i++){
        children[i]->draw(renderPass);
    }
}

/////////////////////////////////////////////////
//position
/////////////////////////////////////////////////

void Object3D::setPosition(glm::vec3 p){

    if(parent == nullptr){
        setLocalPosition(p);
        return;
    }
    
    glm::vec3 parentPos = parent->getPosition();
    glm::mat4 parentMat = glm::translate(glm::mat4(1), parentPos);
    glm::mat4 targetMat = glm::translate(glm::mat4(1), p);
    *p_tMatrix = glm::inverse(parentMat) * targetMat;
}

void Object3D::setLocalPosition(glm::vec3 p){
    *p_tMatrix = glm::translate(glm::mat4(1), p);
    
}

glm::vec3 Object3D::getPosition() const {
    if(parent == nullptr){
        return getLocalPosition();
    }
    
    glm::mat4 m = getModelMatrix();
    return glm::vec3(m[3][0], m[3][1], m[3][2]);
}

glm::vec3 Object3D::getLocalPosition() const {
    glm::mat4 tMat = *p_tMatrix;
    return glm::vec3(tMat[3][0], tMat[3][1], tMat[3][2]);
}

/////////////////////////////////////////////////
//scale
/////////////////////////////////////////////////

void Object3D::setScale(glm::vec3 s){
    if(parent == nullptr){
        setLocalScale(s);
        return;
    }
    
    glm::vec3 parentScale = parent->getScale();
    glm::mat4 parentMat = glm::translate(glm::mat4(1), parentScale);
    glm::mat4 targetMat = glm::translate(glm::mat4(1), s);
    *p_sMatrix = glm::inverse(parentMat) * targetMat;
}

void Object3D::setLocalScale(glm::vec3 s){
    *p_sMatrix =  glm::scale(glm::mat4(1.0f), s);
}

glm::vec3 Object3D::getScale() const {
    if(parent == nullptr){
        return getLocalScale();
    }
    glm::mat4 m = getModelMatrix();
    float sx = glm::length(glm::vec3(m[0][0], m[0][1], m[0][2]));
    float sy = glm::length(glm::vec3(m[1][0], m[1][1], m[1][2]));
    float sz = glm::length(glm::vec3(m[2][0], m[2][1], m[2][2]));
    return glm::vec3(sx, sy, sz);
}



glm::vec3 Object3D::getLocalScale() const {
    glm::mat4 sMat = *p_sMatrix;
    return glm::vec3(sMat[0][0], sMat[1][1], sMat[2][2]);
}

/////////////////////////////////////////////////
//rotate
/////////////////////////////////////////////////

void Object3D::setAngleAxis(float angle, glm::vec3 axis){
    glm::quat q = glm::angleAxis(glm::radians(angle), glm::normalize(axis));
    *p_rMatrix = glm::toMat4(q);
}

void Object3D::setQuaternion(glm::quat q){
    if(parent == nullptr){
        setLocalQuaternion(q);
        return;
    }
    glm::mat4 parentMat = glm::toMat4(getQuaternion());
    glm::mat4 targetMat = glm::toMat4(q);
    *p_rMatrix = glm::inverse(parentMat) * targetMat;
}

void Object3D::setLocalQuaternion(glm::quat q){
    *p_rMatrix = glm::toMat4(q);
}


void Object3D::setEularAngle(glm::vec3 angle){
    if(parent == nullptr){
        setLocalEularAngle(angle);
        return;
    }
    glm::mat4 parentMat = glm::toMat4(getQuaternion());
    glm::quat targetQuat = glm::quat(angle * 2.0f * glm::pi<float>() / 360.0f);
    glm::mat4 targetMat = glm::toMat4(targetQuat);
    *p_rMatrix = glm::inverse(parentMat) * targetMat;
}

void Object3D::setLocalEularAngle(glm::vec3 angle){
    glm::quat q = glm::quat(angle * 2.0f * glm::pi<float>() / 360.0f);
    *p_rMatrix = glm::toMat4(q);
}



glm::vec3 Object3D::getEulerAnlge() const{
    if(parent == nullptr){
        return getLocalEulerAnlge();
    }
    
    glm::quat q = getQuaternion();
    return glm::eulerAngles(q) * 360.0f / (glm::pi<float>() * 2.0f);
}

glm::vec3 Object3D::getLocalEulerAnlge() const{
    glm::quat q = getLocalQuaternion();
    return glm::eulerAngles(q) * 360.0f / (glm::pi<float>() * 2.0f);
    
}

glm::quat Object3D::getQuaternion() const{
    if(parent == nullptr){
        return getLocalQuaternion();
    }
    glm::mat4 m = getModelMatrix();
    float sx = glm::length(glm::vec3(m[0][0], m[0][1], m[0][2]));
    float sy = glm::length(glm::vec3(m[1][0], m[1][1], m[1][2]));
    float sz = glm::length(glm::vec3(m[2][0], m[2][1], m[2][2]));
    
    float dat = glm::determinant(m);
    if(dat < 0) sx = -1 * sx;
    
    float invSX = 1.0f / sx;
    float invSY = 1.0f / sy;
    float invSZ = 1.0f / sz;
    
    m[0][0] *= invSX;
    m[0][1] *= invSX;
    m[0][2] *= invSX;
    
    m[1][0] *= invSY;
    m[1][1] *= invSY;
    m[1][2] *= invSY;
    
    m[2][0] *= invSZ;
    m[2][1] *= invSZ;
    m[2][2] *= invSZ;
    
    return glm::quat(m);
}

glm::quat Object3D::getLocalQuaternion() const{
    return glm::quat(*p_rMatrix);
}

glm::mat4 Object3D::getModelMatrix() const{
    if(parent == nullptr){
        return getLocalModelMatrix();
    }
    
    glm::mat4 parentMatrix = parent->getModelMatrix();
    return parentMatrix * getLocalModelMatrix();
}

glm::mat4 Object3D::getLocalModelMatrix()const{
    return *p_tMatrix * *p_rMatrix * *p_sMatrix;
}

void Object3D::addChild(Object3D *object){
    object->updateParent(this);
    children.push_back(object);
}

std::vector<Object3D*> Object3D::getChildren() const{
    return children;
}

void Object3D::addBheaviour(Object3DBehaviour *behaviour){
    behaviour->p_tMatrix = p_tMatrix;
    behaviour->p_sMatrix = p_sMatrix;
    behaviour->p_rMatrix = p_rMatrix;

    behaviours.push_back(behaviour);
}

void Object3D::addBehaviour(std::string name){
    Object3DBehaviour* behaviour = Object3DBehaviour::create(name);
    behaviour->p_tMatrix = p_tMatrix;
    behaviour->p_sMatrix = p_sMatrix;
    behaviour->p_rMatrix = p_rMatrix;
    
    behaviours.push_back(behaviour);
}








