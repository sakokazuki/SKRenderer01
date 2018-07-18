//
//  Renderer.hpp
//  Game01
//
//  Created by kazuki sako on 2018/01/29.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#ifndef Renderer_hpp
#define Renderer_hpp

#include <stdio.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/ext.hpp>
#include <GL/glew.h>
#include "../system/Object3D.hpp"
#include "../scenes/Scene.hpp"

class Renderer{
private:
    Scene::Scene* scene;
protected:
public:
    int windowW;
    int windowH;
    
    void setScene(Scene::Scene* s);
    Renderer(int ww, int wh);
    virtual void render(Scene::Scene* scene) const;
    
    
    
};

#endif /* Renderer_hpp */
