//
//  Torus.hpp
//  Game01
//
//  Created by kazuki sako on 2018/01/11.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#ifndef Torus_hpp
#define Torus_hpp

#include <stdio.h>

class Torus{
private:
    unsigned int vaoHandle;
    int faces, rings, sides;
    
    void generateVerts(float * , float * ,float *, unsigned int *, float , float);
    
public:
    Torus(float, float, int, int);
    
    void render() const;
};
#endif /* Torus_hpp */
