//
//  TextureMeshMaterial.hpp
//  Game01
//
//  Created by kazuki sako on 2018/04/06.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#ifndef TextureMeshMaterial_hpp
#define TextureMeshMaterial_hpp

#include <stdio.h>

#include "MeshMaterial.hpp"

class TextureMeshMaterial:public MeshMaterial{
private:
    
public:
    TextureMeshMaterial();
    GLuint mainTex;
    void setUniforms(RenderPass* renderPass) override;
    ~TextureMeshMaterial();
};

#endif /* TextureMeshMaterial_hpp */
