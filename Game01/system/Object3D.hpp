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

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include "glm/ext.hpp"
#include <typeinfo>
#include <cxxabi.h>
#include <iostream>



class Object3D{
private:
    void onChangeRotation();
    void onChangeQuaternion();
    void updateRMatrix();
protected:
    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 rotation;
    glm::quat quaternion;
    glm::mat4 tMatrix, sMatrix, rMatrix;
public:
    Object3D();
    
    virtual void update();
    void setTranslate(float x, float y, float z);
    void setScale(float x, float y, float z);
    void setAngleAxis(float, glm::vec3 axis);
    void setRotation(glm::vec3 r);
    void setQuaternion(glm::quat q);
    
    virtual char* classname();

    
    glm::vec3 getPosition() const;
    glm::vec3 getScale() const;
    glm::vec3 getEulerAnlge() const;
    glm::quat getQuaternion() const;
    glm::mat4 getModelMatrix() const;
    
};

#endif /* _DObject_hpp */
