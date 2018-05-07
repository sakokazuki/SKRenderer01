//
//  PbrShadingPass.hpp
//  Game01
//
//  Created by kazuki sako on 2018/04/30.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#ifndef PbrShadingPass_hpp
#define PbrShadingPass_hpp

#include <stdio.h>

#include "RenderPass.hpp"
#include "../meshes/QuadScreenMesh.hpp"

class PbrShadingPass:public RenderPass{
private:
    GLint KdLoc, ShininessLoc, lightPositionLoc, lightIntensityLoc, postexloc, normtexloc, coltexloc, shadowtexloc;
    Mesh* quad;
public:
    PbrShadingPass();
    void draw() override;
    void init(Light* l, Camera* c, std::vector<Mesh*> m) override;
    
};

#endif /* PbrShadingPass_hpp */
