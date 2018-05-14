//
//  DirectionalLight.hpp
//  Game01
//
//  Created by kazuki sako on 2018/05/13.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#ifndef DirectionalLight_hpp
#define DirectionalLight_hpp

#include <stdio.h>
#include "./Light.hpp"
class DirectionalLight: public Light{
public:
    DirectionalLight(glm::vec3 color, float intensity);
    glm::vec3 lookPos;
    void update() override;
    void lighting(RenderPass *renderPass, int index) override;
};

#endif /* DirectionalLight_hpp */
