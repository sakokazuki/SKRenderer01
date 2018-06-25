//
//  Object3DBehaviour.hpp
//  Game01
//
//  Created by kazuki sako on 2018/06/23.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#ifndef Object3DBehaviour_hpp
#define Object3DBehaviour_hpp

#include <stdio.h>
#include "Object3D.hpp"

class Object3DBehaviour: public Object3D {
private:
    Object3D* manager;
public:
    Object3DBehaviour();
    void update() override;
    ~Object3DBehaviour();
    
};



#endif /* Object3DBehaviour_hpp */

