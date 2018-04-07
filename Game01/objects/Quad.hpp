//
//  Quad.hpp
//  Game01
//
//  Created by kazuki sako on 2018/01/24.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#ifndef Quad_hpp
#define Quad_hpp

#include <stdio.h>
class Quad
{
private:
    unsigned int vaoHandle;
    int faces;
    
public:
    Quad();
    
    void render() const;
};



#endif /* Quad_hpp */
