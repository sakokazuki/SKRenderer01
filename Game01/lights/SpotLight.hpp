//
//  SpotLight.hpp
//  Game01
//
//  Created by kazuki sako on 2018/05/13.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#ifndef SpotLight_hpp
#define SpotLight_hpp

#include <stdio.h>
#include "./Light.hpp"

class SpotLight:public Light{
    
public:
    SpotLight(glm::vec3 color, float intensity, float distance, float angle, float penumbra, float decay);
    glm::vec3 lookPos;
    float distance;
    float angle;
    float penumbra;
    float decay;
    void update() override;
    void lighting(RenderPass *renderPass, int index) override;
};

#endif /* SpotLight_hpp */
