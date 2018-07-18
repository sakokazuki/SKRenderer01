//
//  TestApp.hpp
//  Game01
//
//  Created by kazuki sako on 2018/07/11.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#ifndef TestApp_hpp
#define TestApp_hpp

#include <stdio.h>
#include "AppBase.hpp"


namespace app {
    class TestApp : public AppBase{
    public:
        TestApp(Window* window);
        void loop() override;
        ~TestApp();
    };
}

#endif /* TestApp_hpp */
