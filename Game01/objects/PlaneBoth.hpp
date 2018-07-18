//
//  PlaneBoth.hpp
//  Game01
//
//  Created by kazuki sako on 2018/06/17.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#ifndef PlaneBoth_hpp
#define PlaneBoth_hpp

#include <stdio.h>
class PlaneBoth
{
private:
    unsigned int vaoHandle;
    int faces;
    
public:
    PlaneBoth(float, float, int, int);
    
    void render() const;
};

#endif /* PlaneBoth_hpp */


