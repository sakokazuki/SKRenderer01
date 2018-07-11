//
//  Scene.cpp
//  Game01
//
//  Created by kazuki sako on 2018/07/09.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#include "Scene.hpp"

namespace Scene{
    Scene::Scene(){
        
    }
    
    void Scene::addMesh(Mesh *mesh){
        meshes.push_back(mesh);
    }
    
    std::vector<Mesh*> Scene::getMehses(){
        return meshes;
    }
    
    void Scene::addLight(Light *light){
        lights.push_back(light);
    }
    
    std::vector<Light*> Scene::getLights(){
        return lights;
    }
    
    void Scene::setCamera(Camera *camera){
        this->camera = camera;
    }
    
    Camera* Scene::getCamera(){
        return camera;
    }
    
    void Scene::update(){
        camera->update();
        camera->updateParent(nullptr);
        
        for(int i=0; i<lights.size(); i++){
            lights[i]->update();
            lights[i]->updateParent(nullptr);
        }
        
        for(int i=0; i<meshes.size(); i++){
            meshes[i]->update();
            meshes[i]->updateParent(nullptr);
        }
    }
    
    Scene::~Scene(){
        
        
    }
    
}
