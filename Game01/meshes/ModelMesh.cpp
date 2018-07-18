//
//  ModelMesh.cpp
//  Game01
//
//  Created by kazuki sako on 2018/01/25.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#include "ModelMesh.hpp"

ModelMesh::ModelMesh(const char* filename){
    model = new ObjMesh(filename);
}

void ModelMesh::draw() const {
    model->render();
}


void ModelMesh::update(){
    Object3D::update();
}

ModelMesh::~ModelMesh(){
    delete model;
}
