//
//  Object3DBehaviour.cpp
//  Game01
//
//  Created by kazuki sako on 2018/06/23.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#include "Object3DBehaviour.hpp"
#include "./Fractory.h"

Object3DBehaviour::Factory Object3DBehaviour::_factory;

Object3DBehaviour::Object3DBehaviour(){
    
}

void Object3DBehaviour::update(){
    Object3D::update();

}

Object3DBehaviour::~Object3DBehaviour(){
    
}

Object3DBehaviour::Factory::Type Object3DBehaviour::create(Factory::Key const & name){
    return _factory.create(name);
}

