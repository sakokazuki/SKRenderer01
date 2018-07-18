//
//  Object3DBehaviourList.h
//  Game01
//
//  Created by kazuki sako on 2018/07/09.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#ifndef Object3DBehaviourList_h
#define Object3DBehaviourList_h

#include "../behaviours/TestBehaviour.hpp"
#include "./Object3DBehaviour.hpp"

class DefineBehaviours{
private:
    DefineBehaviours();
    
public:
    static void define(){
        static bool isDefine = false;
        if(isDefine == true) return;
        
        Object3DBehaviour::define<behaviour::TestBehaviour>("TestBehaviour");
        isDefine = true;
    }
};


#endif /* Object3DBehaviourList_h */
