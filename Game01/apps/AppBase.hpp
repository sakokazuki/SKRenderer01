//
//  AppBase.hpp
//  Game01
//
//  Created by kazuki sako on 2018/07/11.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#ifndef AppBase_hpp
#define AppBase_hpp

#include <stdio.h>
#include "../renderers/Renderer.hpp"
#include "../scenes/Scene.hpp"
#include "../system/Window.hpp"

namespace app {
    class AppBase{
    private:
        Renderer *renderer;
        Scene::Scene *scene;
    public:
        AppBase(Window *window);
        void setRenderer(Renderer* r);
        void setScene(Scene::Scene* s);
        virtual void loop();
        ~AppBase();
    };
}

#endif /* AppBase_hpp */
