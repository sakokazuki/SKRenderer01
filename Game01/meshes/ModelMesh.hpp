//
//  ModelMesh.hpp
//  Game01
//
//  Created by kazuki sako on 2018/01/25.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#ifndef ModelMesh_hpp
#define ModelMesh_hpp

#include <stdio.h>
#include "Mesh.hpp"
#include "../objects/ObjMesh.hpp"

class ModelMesh:public Mesh{
private:
    ObjMesh* model;

public:
    ModelMesh(const char * fileName);
    void draw() const override;
    ~ModelMesh();
};

#endif /* ModelMesh_hpp */

