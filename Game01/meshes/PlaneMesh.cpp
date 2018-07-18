//
//  PlaneMesh.cpp
//  Game01
//
//  Created by kazuki sako on 2018/02/07.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#include "PlaneMesh.hpp"

PlaneMesh::PlaneMesh(){
//    plane = new Plane(1, 1, 1, 1);
    planeBoth = new PlaneBoth(1, 1, 1, 1);
}

void PlaneMesh::draw() const{
//    plane->render();
    planeBoth->render();
}

PlaneMesh::~PlaneMesh(){
//    delete plane;
    delete planeBoth;
}
