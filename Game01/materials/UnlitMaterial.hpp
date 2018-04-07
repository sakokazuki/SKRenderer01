//
//  UnlitMaterial.hpp
//  Game01
//
//  Created by kazuki sako on 2018/02/04.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#ifndef UnlitMaterial_hpp
#define UnlitMaterial_hpp

#include <stdio.h>

#include "ShaderMaterial.hpp"

class UnlitMaterial:public ShaderMaterial{
private:
    GLuint shadowmapLoc, shadowMatrixLoc;
    
public:
    UnlitMaterial();
    glm::mat4 lightPV, viewMatrix, projectionMatrix;
    void update();
    void setmvp() const;
};


#endif /* UnlitMaterial_hpp */
