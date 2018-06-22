//
//  TorusMesh.cpp
//  Game01
//
//  Created by kazuki sako on 2018/01/24.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#include "TorusMesh.hpp"

TorusMesh::TorusMesh(){
    torus = new Torus(0.7f * 2, 0.3f * 2, 50, 50);
}

void TorusMesh::draw() const{
    torus->render();
}


void TorusMesh::update(){
    Object3D::update();
}

TorusMesh::~TorusMesh(){
    delete torus;
}


