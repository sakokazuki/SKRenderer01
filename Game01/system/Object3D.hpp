//
//  Object3D.hpp
//  Game01
//
//  Created by kazuki sako on 2018/02/07.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#ifndef _DObject_hpp
#define _DObject_hpp

#include <stdio.h>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include "glm/ext.hpp"
#include <typeinfo>
#include <cxxabi.h>
#include <iostream>

class RenderPass;
class Object3DBehaviour;

class Object3D{
private:
    std::vector<Object3D*> children;
    std::vector<Object3D*> behaviours;
    glm::mat4 tMatrix, sMatrix, rMatrix;
    glm::mat4 *p_tMatrix, *p_sMatrix, *p_rMatrix;
    Object3D *parent;
    
protected:
    
public:
    Object3D();
    bool isDebug;
    
    virtual void update();
    
    
    virtual void draw(RenderPass *renderPass) const;
    
    //set
    void setPosition(glm::vec3 p);
    void setLocalPosition(glm::vec3 p);
    void setScale(glm::vec3 s);
    void setLocalScale(glm::vec3 s);
    void setAngleAxis(float, glm::vec3 axis);
    void setEularAngle(glm::vec3 angle);
    void setLocalEularAngle(glm::vec3 angle);
    void setQuaternion(glm::quat q);
    void setLocalQuaternion(glm::quat q);
    
    void addChild(Object3D *object);
    void addBheaviour(Object3DBehaviour *behaviour);
    
    void updateParent(Object3D *object);
    
    virtual char* classname();
    
    //get
    glm::vec3 getPosition() const;
    glm::vec3 getLocalPosition() const;
    glm::vec3 getScale() const;
    glm::vec3 getLocalScale() const;
    glm::vec3 getEulerAnlge() const;
    glm::vec3 getLocalEulerAnlge() const;
    glm::quat getQuaternion() const;
    glm::quat getLocalQuaternion() const;
    glm::mat4 getModelMatrix() const;
    glm::mat4 getLocalModelMatrix() const;
    std::vector<Object3D*> getChildren() const;
    
    
};

#endif /* _DObject_hpp */
