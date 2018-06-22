//
//  Scene.hpp
//  Game01
//
//  Created by kazuki sako on 2018/01/29.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#ifndef Scene_hpp
#define Scene_hpp

#include <stdio.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/ext.hpp>
#include <gli/gli.hpp>
#include <GL/glew.h>
#include "../system/Object3D.hpp"

class Scene{
protected:
public:
    int windowW;
    int windowH;
    Scene(int ww, int wh);
    virtual void render() const;
    
    
    
};

#endif /* Scene_hpp */
