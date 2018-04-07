//
//  Light.hpp
//  Game01
//
//  Created by kazuki sako on 2018/02/03.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#ifndef Light_hpp
#define Light_hpp

#include <stdio.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "../system/frustum.h"

class Light{
private:
    Frustum *lightFrustum;
    glm::mat4 shadowBias;
    glm::vec4 position;
    glm::vec3 intensity;
public:
    Light();
    glm::mat4 getProjectionMatrix() const;
    glm::mat4 getViewMatrix() const;
    glm::mat4 getPVMatrix() const;
    glm::vec4 getPosition() const;
    glm::vec3 getIntensity() const;
};

#endif /* Light_hpp */
