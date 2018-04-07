//
//  TorusMesh.hpp
//  Game01
//
//  Created by kazuki sako on 2018/01/24.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#ifndef TorusMesh_hpp
#define TorusMesh_hpp

#include <stdio.h>
#include "../objects/Torus.hpp"
#include "Mesh.hpp"

class TorusMesh:public Mesh{
private:
    Torus* torus;
public:
    TorusMesh();
    void draw() const override;
    ~TorusMesh();
};

#endif /* TorusMesh_hpp */
