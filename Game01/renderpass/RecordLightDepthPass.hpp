//
//  RecordLightDepthPass.hpp
//  Game01
//
//  Created by kazuki sako on 2018/02/08.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#ifndef RecordLightDepthPass_hpp
#define RecordLightDepthPass_hpp

#include <stdio.h>

#include "RenderPass.hpp"

class RecordLightDepthPass:public RenderPass{
private:
public:
    RecordLightDepthPass();
    void drawPass() override;
    void drawObjects(Object3D *object);
    void init(std::vector<Light*> l, Camera* c, std::vector<Mesh*> m) override;
};

#endif /* RecordLightDepthPass_hpp */
