//
//  Mesh.hpp
//  Game01
//
//  Created by kazuki sako on 2018/02/07.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <stdio.h>
#include "glm/ext.hpp"
#include <iostream>
#include "../system/Object3D.hpp"
#include "../meshMaterials/MeshMaterial.hpp"
class RenderPass;

//#include "../renderpass/RenderPass.hpp"


class Mesh:public Object3D{
protected:
public:
    Mesh();
    MeshMaterial *meshMaterial;
    void draw(RenderPass *renderPass) const override;
    virtual void draw() const;
    ~Mesh();
    
};
#endif /* Mesh_hpp */
