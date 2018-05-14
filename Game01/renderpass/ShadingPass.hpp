//
//  ShadingPass.hpp
//  Game01
//
//  Created by kazuki sako on 2018/02/08.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#ifndef ShadingPass_hpp
#define ShadingPass_hpp

#include <stdio.h>

#include "RenderPass.hpp"
#include "../meshes/QuadScreenMesh.hpp"

class ShadingPass:public RenderPass{
private:
    GLint KdLoc, ShininessLoc, lightPositionLoc, lightIntensityLoc, postexloc, normtexloc, coltexloc, shadowtexloc;
    Mesh* quad;
public:
    ShadingPass();
    void draw() override;
    void init(std::vector<Light*> l, Camera* c, std::vector<Mesh*> m) override;
    
};

#endif /* ShadingPass_hpp */
