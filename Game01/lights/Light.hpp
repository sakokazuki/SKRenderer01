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
#include "../system/3DObject.hpp"
class RenderPass;

class Light:public _3DObject{
private:
    glm::mat4 shadowBias;
    float intensity;
    glm::vec3 color;
protected:
    glm::mat4 projectionMatrix;
    glm::mat4 viewMatrix;
public:
    Light(glm::vec3 color, float intensity);
    glm::mat4 getProjectionMatrix() const;
    glm::mat4 getViewMatrix() const;
    glm::mat4 getPVMatrix() const;
    glm::vec4 getPosition() const;
    glm::vec3 getIntensity() const;
    
    bool enable;
    bool castShadow;
    
    virtual void update();
    virtual void lighting(RenderPass *renderPass, int index);
};

#endif /* Light_hpp */
