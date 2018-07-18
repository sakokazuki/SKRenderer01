//
//  QuadScreenMesh.hpp
//  Game01
//
//  Created by kazuki sako on 2018/02/08.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#ifndef QuadScreenMesh_hpp
#define QuadScreenMesh_hpp

#include <stdio.h>
#include "Mesh.hpp"
#include "../objects/Quad.hpp"

class QuadScreenMesh:public Mesh{
private:
    Quad* quad;
    
public:
    QuadScreenMesh();
    void draw() const override;
    ~QuadScreenMesh();
};

#endif /* QuadScreenMesh_hpp */
