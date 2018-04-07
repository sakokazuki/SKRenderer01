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
    void draw() override;
    void init(Light* l, Camera* c, std::vector<Mesh*> m) override;
    
};

#endif /* GBufferPass_hpp */
