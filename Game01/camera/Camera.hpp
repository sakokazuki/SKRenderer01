//
//  Camera.hpp
//  Game01
//
//  Created by kazuki sako on 2018/02/07.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include <stdio.h>

#include "../system/Object3D.hpp"
class Camera:public Object3D{
public:
    Camera(int w, int h);
    glm::vec3 lookPos;
    glm::mat4 viewMatrix, projectionMatrix;
    int width, height;
    void update() override;
    
};

#endif /* Camera_hpp */
