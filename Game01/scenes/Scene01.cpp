//
//  Scene01.cpp
//  Game01
//
//  Created by kazuki sako on 2018/02/07.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#include "Scene01.hpp"


Scene01::Scene01(int ww, int wh):Scene(ww, wh){
    glClearColor(1.0f,1.0f,1.0f,1.0f);

    
    Light* spotLight = new SpotLight(glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 20.0f, 25.0f, 1.0f, 1.0f);
    spotLight->setPosition(glm::vec3(2, 8, 1));
    lights.push_back(spotLight);
    
    Light* directionalLight = new DirectionalLight(glm::vec3(1.0f, 1.0f, 1.0f), 0.1f);
    directionalLight->setPosition(glm::vec3(-2, 3, -3));
    directionalLight->castShadow = true;
    
    lights.push_back(directionalLight);
    
    
    Light* pointLight0 = new PointLight(glm::vec3(0.9f, 0.0f, 0.0f), 2.0f, 5.0f, 1.0f);
    pointLight0->setPosition(glm::vec3(3, 3, 0));
    lights.push_back(pointLight0);
    
    Light* pointLight1 = new PointLight(glm::vec3(0.0f, 0.9f, 0.0f), 2.0f, 5.0f, 1.0f);
    pointLight1->setPosition(glm::vec3(-3, 3, 0));
    lights.push_back(pointLight1);
    
    Light* pointLight2 = new PointLight(glm::vec3(0.0f, 0.0f, 0.9f), 2.0f, 5.0f, 1.0f);
    pointLight2->setPosition(glm::vec3(0, 3, 3));
    lights.push_back(pointLight2);
    
    Light* pointLight3 = new PointLight(glm::vec3(0.9f, 0.0f, 0.9f), 2.0f, 5.0f, 1.0f);
    pointLight3->setPosition(glm::vec3(0, 3, -3));
    lights.push_back(pointLight3);
    
    camera = new Camera(windowW, windowH);
    camera->setPosition(glm::vec3(0, 2, 5));
    
    
    plane = new PlaneMesh();
    plane->setPosition(glm::vec3(0, 0, 0));
    plane->setScale(glm::vec3(20, 20, 20));
    
    
    
    groundMeshMat = new PbrMeshMaterial();
    groundMeshMat->metallic = 0.5;
    groundMeshMat->roughness = 0.5;
    plane->meshMaterial = groundMeshMat;
    
    
    
    torus = new TorusMesh();
    torus->setPosition(glm::vec3(0, 2, -1));
    torus->setScale(glm::vec3(0.5, 0.5, 0.5));
    torusMeshMat = new PbrMeshMaterial();
    torusMeshMat->metallic = 0.5;
    torusMeshMat->roughness = 0.5;
    torus->meshMaterial = torusMeshMat;
    
    
    model = new ModelMesh("assets/objs/teapot.obj");
    model->setPosition(glm::vec3(0, 0, -3));
    model->setScale(glm::vec3(0.5, 0.5, 0.5));
    model->setEularAngle(glm::vec3(90, 0, 0));
    teapotMeshMat = new PbrMeshMaterial();
    teapotMeshMat->metallic = 0.5;
    teapotMeshMat->roughness = 0.5;
    model->meshMaterial = teapotMeshMat;
//    model->addBheaviour(test);
    model->addBehaviour("TestBehaviour");
    
    childTorus = new TorusMesh;
    
    
    childTorus->isDebug = true;
    model->addChild(childTorus);
    childTorus->setScale(glm::vec3(0.5, 0.5, 0.5));
    childTorus->setLocalPosition(glm::vec3(5, 0, 0));
    childTorus->setLocalEularAngle(glm::vec3(90, 0, 0));

    
    meshes.push_back(model);
//    meshes.push_back(torus);
    meshes.push_back(plane);
    
    
    
    shadowmapPass = new ShadowmapPass();
    shadowmapPass->init(lights, camera, meshes);
    
    recordLightDepthPass = new RecordLightDepthPass();
    recordLightDepthPass->init(lights, camera, meshes);
    
    gBufferPass = new GBufferPass();
    gBufferPass->init(lights, camera, meshes);
    
    shadingPass = new PbrShadingPass();
    shadingPass->init(lights, camera, meshes);

    
    //FBO 1 -----------------------------------------------------------
    GLfloat border[] = {1.0f, 0.0f, 0.0f, 0.0f};
    glGenTextures(1, &depthTex);
    glBindTexture(GL_TEXTURE_2D, depthTex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, windowW*2, windowH*2, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LESS);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, depthTex);
    
    glGenFramebuffers(1, &shadowFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, shadowFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTex, 0);
    
    GLenum drawBuffers[] = {GL_NONE};
    glDrawBuffers(1, drawBuffers);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
    //FBO 2 -----------------------------------------------------------
    glGenFramebuffers(1, &shadowmapFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, shadowmapFBO);
    
    glGenRenderbuffers(1, &shadowDepthBuf);
    glBindRenderbuffer(GL_RENDERBUFFER, shadowDepthBuf);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, windowW*2, windowH*2);
    
    glGenTextures(1, &unlitColorTex);
    glBindTexture(GL_TEXTURE_2D, unlitColorTex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, windowW*2, windowH*2, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, shadowDepthBuf);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, unlitColorTex, 0);
    
    GLenum drawbuffers2[] = {GL_NONE, GL_COLOR_ATTACHMENT0};
    glDrawBuffers(2, drawbuffers2);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
    
    //FBO 3 -----------------------------------------------------------
    glGenFramebuffers(1, &deferredFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, deferredFBO);
    
    glGenRenderbuffers(1, &depthBuf);
    glBindRenderbuffer(GL_RENDERBUFFER, depthBuf);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, windowW*2, windowH*2);
    
    glGenTextures(1, &posTex);
    glBindTexture(GL_TEXTURE_2D, posTex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, windowW*2, windowH*2, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    glGenTextures(1, &normTex);
    glBindTexture(GL_TEXTURE_2D, normTex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, windowW*2, windowH*2, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    

    glGenTextures(1, &colorTex);
    glBindTexture(GL_TEXTURE_2D, colorTex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, windowW*2, windowH*2, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuf);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, posTex, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, normTex, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, colorTex, 0);
    
    GLenum drawBuffers3[] = {GL_NONE, GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2};
    glDrawBuffers(4, drawBuffers3);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
    
    //test texture
    if(!greenTex.loadTexture("assets/images/green.dds")){
        std::cout << "texture load is failed" << std::endl;
    }
    
    if(!groundTex.loadTexture("assets/images/floor.dds")){
        std::cout << "texture load is failed" << std::endl;
    }

    
    groundMeshMat->mainTex = groundTex.getID();
    torusMeshMat->mainTex = greenTex.getID();
    teapotMeshMat->mainTex = greenTex.getID();
    
    GLubyte whiteTexColor[] = { 255, 255, 255, 255 };
    glGenTextures(1, &whiteTex);
    glBindTexture(GL_TEXTURE_2D,whiteTex);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,1,1,0,GL_RGBA,GL_UNSIGNED_BYTE,whiteTexColor);
        
}


void Scene01::render() const{
    Scene::render();
    camera->update();
//    camera->updateWorldMatrix(glm::mat4());
    for(int i=0; i<lights.size(); i++){
        lights[i]->update();
//        lights[i]->updateWorldMatrix(glm::mat4());
    }
    for(int i=0; i<meshes.size(); i++){
        meshes[i]->update();
//        meshes[i]->updateWorldMatrix(glm::mat4());
        meshes[i]->updateParent(nullptr);
    }

    
    
    glEnable(GL_DEPTH_TEST);
    
    
    
    //pass1 record depth ====================================
    glBindFramebuffer(GL_FRAMEBUFFER, shadowFBO);
    
    glClear(GL_DEPTH_BUFFER_BIT);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);

    glUseProgram(recordLightDepthPass->prog);
    recordLightDepthPass->drawPass();
    glUseProgram(0);
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);


    //pass2 create shadowmap ====================================
    glBindFramebuffer(GL_FRAMEBUFFER, shadowmapFBO);

    glEnable(GL_CULL_FACE | GL_DEPTH_TEST);
    glCullFace(GL_FRONT);

    glUseProgram(shadowmapPass->prog);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shadowmapPass->setTextureUniform("ShadowMap", 0, depthTex);
    shadowmapPass->drawPass();
    glUseProgram(0);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
//
    //pass3 create g-buffer ====================================
    glBindFramebuffer(GL_FRAMEBUFFER, deferredFBO);

    glEnable(GL_CULL_FACE | GL_DEPTH_TEST);

    glCullFace(GL_BACK);

    glUseProgram(gBufferPass->prog);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    gBufferPass->drawPass();
    glUseProgram(0);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);


    //pass4 shading ====================================
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);

    glUseProgram(shadingPass->prog);

    shadingPass->setTextureUniform("PositionTex", 0, posTex);
    shadingPass->setTextureUniform("NormalTex", 1, normTex);
    shadingPass->setTextureUniform("ColorTex", 2, colorTex);
    shadingPass->setTextureUniform("ShadowmapTex", 3, unlitColorTex);
    shadingPass->setTextureUniform("TestTex", 4, depthTex);
    shadingPass->drawPass();
    glUseProgram(0);

}


