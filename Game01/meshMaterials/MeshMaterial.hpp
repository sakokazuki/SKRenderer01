//
//  MeshMaterial.hpp
//  Game01
//
//  Created by kazuki sako on 2018/02/27.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#ifndef MeshMaterial_hpp
#define MeshMaterial_hpp

#include <stdio.h>
#include <map>
#include <GL/glew.h>
#include "../renderpass/RenderPass.hpp"


class MeshMaterial{
public:
    MeshMaterial();
    virtual void setUniforms(RenderPass* renderPass);
    ~MeshMaterial();
};

#endif /* MeshMaterial_hpp */
