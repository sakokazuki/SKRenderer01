//
//  QuadScreenMesh.cpp
//  Game01
//
//  Created by kazuki sako on 2018/02/08.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#include "QuadScreenMesh.hpp"

QuadScreenMesh::QuadScreenMesh(){
    quad = new Quad();
    
}

void QuadScreenMesh::draw() const{
    quad->render();
}

QuadScreenMesh::~QuadScreenMesh(){
    delete quad;
}
