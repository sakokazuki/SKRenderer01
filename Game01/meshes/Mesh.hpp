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
#include "../system/3DObject.hpp"
#include "../meshMaterials/MeshMaterial.hpp"
class RenderPass;
//#include "../renderpass/RenderPass.hpp"


class Mesh:public _3DObject{
protected:
public:
    Mesh();
    MeshMaterial *meshMaterial;
    virtual void draw() const;
    virtual void draw(RenderPass *renderPass) const;
    ~Mesh();
    
};
#endif /* Mesh_hpp */
