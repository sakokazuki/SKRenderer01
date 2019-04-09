//
//  TestApp.cpp
//  Game01
//
//  Created by kazuki sako on 2018/07/11.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#include "TestApp.hpp"

#include "../renderers/Renderer01.hpp"
#include "../meshMaterials/PbrMeshMaterial.hpp"
#include "../system/zTexture.hpp"
#include "../lights/Light.hpp"
#include "../lights/SpotLight.hpp"
#include "../lights/DirectionalLight.hpp"
#include "../lights/PointLight.hpp"
#include "../camera/Camera.hpp"
#include "../meshes/TorusMesh.hpp"
#include "../meshes/PlaneMesh.hpp"
#include "../meshes/ModelMesh.hpp"
#include "../meshes/Mesh.hpp"
#include "../system/Object3DBehaviour.hpp"


namespace app {
    TestApp::TestApp(Window *window) : app::AppBase(window){
        
        const GLint *const size(window->getViewport());
        int windowW = size[2];
        int windowH = size[3];
        Renderer* renderer = new Renderer01(windowW, windowH);
        Scene::Scene* scene = new Scene::Scene();
        
        setRenderer(renderer);
        setScene(scene);
        
        Light* spotLight = new SpotLight(glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 20.0f, 25.0f, 1.0f, 1.0f);
        spotLight->setPosition(glm::vec3(2, 8, 1));
        scene->addLight(spotLight);
        
        Light* directionalLight = new DirectionalLight(glm::vec3(1.0f, 1.0f, 1.0f), 0.1f);
        directionalLight->setPosition(glm::vec3(-2, 3, -3));
        directionalLight->castShadow = true;
        scene->addLight(directionalLight);
        
        
        Light* pointLight0 = new PointLight(glm::vec3(0.9f, 0.0f, 0.0f), 2.0f, 5.0f, 1.0f);
        pointLight0->setPosition(glm::vec3(3, 3, 0));
        scene->addLight(pointLight0);
        
        
        Light* pointLight1 = new PointLight(glm::vec3(0.0f, 0.9f, 0.0f), 2.0f, 5.0f, 1.0f);
        pointLight1->setPosition(glm::vec3(-3, 3, 0));
        scene->addLight(pointLight1);
        
        Light* pointLight2 = new PointLight(glm::vec3(0.0f, 0.0f, 0.9f), 2.0f, 5.0f, 1.0f);
        pointLight2->setPosition(glm::vec3(0, 3, 3));
        scene->addLight(pointLight2);
        
        Light* pointLight3 = new PointLight(glm::vec3(0.9f, 0.0f, 0.9f), 2.0f, 5.0f, 1.0f);
        pointLight3->setPosition(glm::vec3(0, 3, -3));
        scene->addLight(pointLight3);
        
        Camera* camera = new Camera(windowW, windowH);
        camera->setPosition(glm::vec3(0, 5, 6));
        scene->setCamera(camera);
        
        
        Mesh* plane = new PlaneMesh();
        plane->setPosition(glm::vec3(0, 0, 0));
        plane->setScale(glm::vec3(20, 1, 20));
        
        
        
        PbrMeshMaterial* groundMeshMat = new PbrMeshMaterial();
        groundMeshMat->metallic = 0.0;
        groundMeshMat->roughness = 0.0;
        plane->meshMaterial = groundMeshMat;
        
        
        
        Mesh* torus = new TorusMesh();
        torus->setPosition(glm::vec3(0, 2, -1));
        torus->setScale(glm::vec3(0.5, 0.5, 0.5));
        PbrMeshMaterial* torusMeshMat = new PbrMeshMaterial();
        torusMeshMat->metallic = 0.5;
        torusMeshMat->roughness = 0.5;
        torus->meshMaterial = torusMeshMat;
		
        Mesh* model = new ModelMesh("assets/objs/teddy.obj");
        model->setPosition(glm::vec3(0, 1, 0));
        model->setScale(glm::vec3(0.06, 0.06, 0.06));
        model->setEularAngle(glm::vec3(90, 0, 0));
        PbrMeshMaterial* teapotMeshMat = new PbrMeshMaterial();
        teapotMeshMat->metallic = 0.5;
        teapotMeshMat->roughness = 0.5;
        model->meshMaterial = teapotMeshMat;
        model->addBehaviour("TestBehaviour");
        
        Mesh* childTorus = new TorusMesh;
        
        
        childTorus->isDebug = true;
        
        childTorus->setScale(glm::vec3(10.5, 10.5, 10.5));
        childTorus->setLocalPosition(glm::vec3(50.6, 2, 0));
        childTorus->setLocalEularAngle(glm::vec3(0, 0, 0));
        
		model->addChild(childTorus);

        scene->addMesh(model);
        scene->addMesh(plane);
        //scene->addMesh(torus);
        
        //test texture
        zTexture greenTex;
        zTexture groundTex;
        if(!greenTex.loadTexture("assets/images/green.png")){
            std::cout << "texture load is failed" << std::endl;
        }
        
        if(!groundTex.loadTexture("assets/images/floor.png")){
            std::cout << "texture load is failed" << std::endl;
        }
        
        groundMeshMat->mainTex = groundTex.getID();
        torusMeshMat->mainTex = groundTex.getID();
        teapotMeshMat->mainTex = groundTex.getID();
        
    }
    
    void TestApp::loop(){
        AppBase::loop();
        
    }
    
    TestApp::~TestApp(){
        
    }
    
}


