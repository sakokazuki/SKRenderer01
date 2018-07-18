//
//  AppBase.cpp
//  Game01
//
//  Created by kazuki sako on 2018/07/11.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#include "AppBase.hpp"

namespace app {
    AppBase::AppBase(Window *window){
        
    }
    
    void AppBase::setScene(Scene::Scene *s){
        scene = s;
    }
    
    void AppBase::setRenderer(Renderer *r){
        renderer = r;
    }
    
    void AppBase::loop(){
		if (renderer && scene) {
			renderer->render(scene);
		}
		else {
			fprintf(stderr, "renderer or scene is null");
		}
        
        
    }
    
    AppBase::~AppBase(){
        
    }
    
}
