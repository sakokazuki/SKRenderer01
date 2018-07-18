//
//  Renderer.cpp
//  Game01
//
//  Created by kazuki sako on 2018/01/29.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#include "Renderer.hpp"

Renderer::Renderer(int ww, int wh){
    windowW = ww;
    windowH = wh;
}

void Renderer::render(Scene::Scene* scene) const{
    
}

void Renderer::setScene(Scene::Scene *s){
    scene = s;
}
