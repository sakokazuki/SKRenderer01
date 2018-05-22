//
//  PointLight.hpp
//  Game01
//
//  Created by kazuki sako on 2018/05/15.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#ifndef PointLight_hpp
#define PointLight_hpp

#include <stdio.h>
#include "./Light.hpp"

class PointLight:public Light {
public:
    PointLight(glm::vec3 color, float intensity, float distance, float decay);
    float distance;
    float decay;
    void update() override;
    void lighting(RenderPass *renderPass, int index) override;

};

#endif /* PointLight_hpp */
