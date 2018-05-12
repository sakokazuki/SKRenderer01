//
//  SceneShadowDeferred.cpp
//  Game01
//
//  Created by kazuki sako on 2018/02/03.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#include "SceneShadowDeferred.hpp"




SceneShadowDeferred::SceneShadowDeferred(int ww, int wh):Scene(ww, wh){
    glClearColor(1.0f,1.0f,1.0f,1.0f);
    light = new Light(glm::vec3(1.0f, 1.0f, 1.0f), 1.0);
    quad = new Quad();

    shadowmappass = new ShadowmapPassMaterial();
    deferredpass = new DeferredPassMaterial();
    deferredmat = new DeferredMaterial();
    unlitmat = new UnlitMaterial();
    
    torus = new Torus(0.7f * 2, 0.3f * 2, 50, 50);
    
    plane = new Plane(1, 1, 1, 1);
    
    

    camera = new Camera(windowW, windowH);
    projectionMatrix = camera->projectionMatrix;
    viewMatrix = camera->viewMatrix;
    
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
    
    //FBO test -----------------------------------------------------------
    glGenFramebuffers(1, &simpleFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, simpleFBO);
    
    glGenTextures(1, &unlitColorTex);
    glBindTexture(GL_TEXTURE_2D, unlitColorTex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, windowW*2, windowH*2, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, unlitColorTex, 0);
    
    GLenum testDrawBuffers[] = {GL_NONE, GL_COLOR_ATTACHMENT0};
    glDrawBuffers(2, testDrawBuffers);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
    //FBO 2 -----------------------------------------------------------
    
    glGenFramebuffers(1, &shadowmapFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, shadowmapFBO);
    
    glGenTextures(1, &shadowTex);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, windowW*2, windowH*2, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, shadowTex, 0);
    
    GLenum shadowmapDrawBuffers[] = {GL_NONE, GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, shadowmapDrawBuffers);
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
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, windowW*2, windowH*2, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    glGenTextures(1, &colorTex);
    glBindTexture(GL_TEXTURE_2D, colorTex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, windowW*2, windowH*2, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    glGenTextures(1, &unlitColorTex2);
    glBindTexture(GL_TEXTURE_2D, unlitColorTex2);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, windowW*2, windowH*2, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuf);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, posTex, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, normTex, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, colorTex, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, GL_TEXTURE_2D, unlitColorTex2, 0);
    
    GLenum drawBuffers2[] = {GL_NONE, GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3};
    glDrawBuffers(5, drawBuffers2);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
}

void SceneShadowDeferred::render() const{
    glEnable(GL_DEPTH_TEST);
    glUseProgram(shadowmappass->prog);
    shadowmappass->lightPV = light->getPVMatrix();
    glBindFramebuffer(GL_FRAMEBUFFER, shadowFBO);
    glClear(GL_DEPTH_BUFFER_BIT);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);

    shadowmappass->viewMatrix = light->getViewMatrix();
    shadowmappass->projectionMatrix = light->getProjectionMatrix();
    shadowmappass->pass1();
    drawScene();


    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glBindFramebuffer(GL_FRAMEBUFFER, shadowmapFBO);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_CULL_FACE);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, depthTex);

    shadowmappass->viewMatrix = viewMatrix;
    shadowmappass->projectionMatrix = projectionMatrix;
    shadowmappass->pass2();
    drawScene();
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glUseProgram(0);
    
    glBindFramebuffer(GL_FRAMEBUFFER, simpleFBO);
    glUseProgram(unlitmat->prog);
    unlitmat->lightPV = light->getPVMatrix();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glDisable(GL_CULL_FACE);
//    glClear(GL_DEPTH_TEST  | GL_COLOR_BUFFER_BIT);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    

    

   

    unlitmat->viewMatrix = viewMatrix;
    unlitmat->projectionMatrix = projectionMatrix;
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, depthTex);
    unlitmat->update();
    drawScene3();


    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glUseProgram(0);

    glUseProgram(deferredpass->prog);
    glBindFramebuffer(GL_FRAMEBUFFER, deferredFBO);
    glClear(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glDisable(GL_DEPTH_TEST);

    deferredpass->viewMatrix = viewMatrix;
    deferredpass->projectionMatrix = projectionMatrix;
    deferredpass->pass1();
    drawScene2();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);



    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, posTex);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, normTex);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, colorTex);
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, unlitColorTex);
    deferredpass->pass2();
    quad->render();

    glUseProgram(0);

    
}

void SceneShadowDeferred::drawScene() const{
    shadowmappass->tMatrix = glm::translate(glm::mat4(), glm::vec3(0, -2, 0));
    shadowmappass->sMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(10.0));
    shadowmappass->setmvp();
    plane->render();
    shadowmappass->sMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0));
    shadowmappass->tMatrix = glm::translate(glm::mat4(), glm::vec3(0, 0, 0));
    shadowmappass->setmvp();
    torus->render();
}

void SceneShadowDeferred::drawScene2() const{
    deferredpass->tMatrix = glm::translate(glm::mat4(), glm::vec3(0, -2, 0));
    deferredpass->sMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(10.0));
    deferredpass->setmvp();
    plane->render();
    deferredpass->sMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0));
    deferredpass->tMatrix = glm::translate(glm::mat4(), glm::vec3(0, 0, 0));
    deferredpass->setmvp();
    torus->render();
}

void SceneShadowDeferred::drawScene3() const{
    unlitmat->tMatrix = glm::translate(glm::mat4(), glm::vec3(0, -2, 0));
    unlitmat->sMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(10.0));
    unlitmat->setmvp();
    plane->render();
    unlitmat->sMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0));
    unlitmat->tMatrix = glm::translate(glm::mat4(), glm::vec3(0, 0, 0));
    unlitmat->setmvp();
    torus->render();
}


