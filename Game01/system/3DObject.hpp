//
//  3DObject.hpp
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
#include "glm/ext.hpp"
#include <iostream>



class _3DObject{
private:
    
public:
    _3DObject();
    glm::vec3 position;
    glm::vec3 scale;
//    glm::vec3 eulerAngle;
//    glm::vec4 quaternion;
    glm::mat4 tMatrix, sMatrix, rMatrix;
    void setTranslate(float x, float y, float z);
    void setScale(float x, float y, float z);
    void setRotate(float, glm::vec3 dir);
    glm::mat4 getModelMatrix() const;
    
};

#endif /* _DObject_hpp */
