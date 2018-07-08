//
//  GBufferPass.hpp
//  Game01
//
//  Created by kazuki sako on 2018/02/08.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#ifndef GBufferPass_hpp
#define GBufferPass_hpp

#include <stdio.h>
#include "RenderPass.hpp"

class GBufferPass:public RenderPass{
private:
public:
    GBufferPass();
    void drawPass() override;
    void drawObjects(Object3D *object);
    void init(std::vector<Light*> l, Camera* c, std::vector<Mesh*> m) override;
    void test(Object3D* mesh);
};

#endif /* GBufferPass_hpp */
