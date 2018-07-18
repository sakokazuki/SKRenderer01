//
//  TestBehaviours.hpp
//  Game01
//
//  Created by kazuki sako on 2018/06/23.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#ifndef TestBehaviour_hpp
#define TestBehaviour_hpp

#include <stdio.h>
#include "../system/Object3DBehaviour.hpp"

namespace behaviour {
    
    class TestBehaviour: public Object3DBehaviour{
    private:
        float testNum;
    public:
        TestBehaviour();
        void update() override;
        ~TestBehaviour();
        
    };
}



#endif /* TestBehaviour_hpp */
