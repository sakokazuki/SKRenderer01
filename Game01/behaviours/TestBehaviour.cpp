//
//  TestBehaviours.cpp
//  Game01
//
//  Created by kazuki sako on 2018/06/23.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#include "TestBehaviour.hpp"

namespace behaviour {
    TestBehaviour::TestBehaviour(){
    }
    
    void TestBehaviour::update(){
        testNum+=1.0f;
        
        glm::vec3 p = getPosition();
//        setRotation(glm::vec3(testNum, 0, 0));
        
        testNum = fmodf(testNum, 360);
		//testNum = 180;
        setAngleAxis(testNum, glm::vec3(0, 1, 0));
//        std::cout <<"angle: " << glm::to_string(getEulerAnlge()) << std::endl;
//        std::cout <<"num  : " << testNum << std::endl;
        
        
        auto q = getQuaternion();
//        if(testNum > 360){
//            testNum = testNum-360;
//        }
//        setPosition(p.x, testNum, p.z);
        
    }
}

