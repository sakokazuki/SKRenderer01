//
//  Plane.hpp
//  Game01
//
//  Created by kazuki sako on 2018/01/12.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#ifndef Plane_hpp
#define Plane_hpp

#include <stdio.h>

class Plane
{
private:
    unsigned int vaoHandle;
    int faces;
    
public:
    Plane(float, float, int, int);
    
    void render() const;
};


#endif /* Plane_hpp */
