//
//  PlaneMesh.hpp
//  Game01
//
//  Created by kazuki sako on 2018/02/07.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#ifndef PlaneMesh_hpp
#define PlaneMesh_hpp

#include <stdio.h>

#include "Mesh.hpp"
#include "../objects/Plane.hpp"
#include "../objects/PlaneBoth.hpp"

class PlaneMesh:public Mesh{
private:
    Plane* plane;
    PlaneBoth* planeBoth;
    
public:
    PlaneMesh();
    void draw() const override;
    ~PlaneMesh();
};

#endif /* PlaneMesh_hpp */
