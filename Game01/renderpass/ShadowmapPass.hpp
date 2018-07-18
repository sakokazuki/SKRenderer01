//
//  ShadowmapPass.hpp
//  Game01
//
//  Created by kazuki sako on 2018/02/07.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#ifndef ShadowmapPass_hpp
#define ShadowmapPass_hpp

#include <stdio.h>

#include "RenderPass.hpp"
class ShadowmapPass:public RenderPass{
private:
    GLint shadowMatrixLoc;
public:
    ShadowmapPass();
    void drawPass() override;
    void drawObjects(Object3D *object, Light *light);
    void init(std::vector<Light*> l, Camera* c, std::vector<Mesh*> m) override;
};

#endif /* ShadowmapPass_hpp */
