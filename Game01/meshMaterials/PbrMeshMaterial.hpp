//
//  PbrMeshMaterial.hpp
//  Game01
//
//  Created by kazuki sako on 2018/04/30.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#ifndef PbrMeshMaterial_hpp
#define PbrMeshMaterial_hpp

#include <stdio.h>

#include "MeshMaterial.hpp"

class PbrMeshMaterial:public MeshMaterial{
private:
    
public:
    PbrMeshMaterial();
    GLuint mainTex;
    float metallic;
    float roughness;
    void setUniforms(RenderPass* renderPass) override;
    ~PbrMeshMaterial();
};

#endif /* PbrMeshMaterial_hpp */
