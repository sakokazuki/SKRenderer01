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
    
    light = new Light();
    camera = new Camera(windowW, windowH);

    plane = new PlaneMesh();
    plane->setTranslate(0, -2, 0);
    plane->setScale(10, 10, 10);
    
    texmat1 = new TextureMeshMaterial();
    plane->meshMaterial = texmat1;
    
    
    torus = new TorusMesh();
    torus->setTranslate(0, 0, 0);
    torus->setScale(1, 1, 1);
    texmat2 = new TextureMeshMaterial();
    torus->meshMaterial = texmat2;
    meshes.push_back(torus);
    
    meshes.push_back(plane);
    shadowmapPass = new ShadowmapPass();
    shadowmapPass->init(light, camera, meshes);
    
    recordLightDepthPass = new RecordLightDepthPass();
    recordLightDepthPass->init(light, camera, meshes);
    
    gBufferPass = new GBufferPass();
    gBufferPass->init(light, camera, meshes);
    
    shadingPass = new ShadingPass();
    shadingPass->init(light, camera, meshes);

    
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
    
    glGenTextures(1, &unlitColorTex);
    glBindTexture(GL_TEXTURE_2D, unlitColorTex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, windowW*2, windowH*2, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
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
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, windowW*2, windowH*2, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    glGenTextures(1, &colorTex);
    glBindTexture(GL_TEXTURE_2D, colorTex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, windowW*2, windowH*2, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
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
    
    texmat1->mainTex = groundTex.getID();
    texmat2->mainTex = greenTex.getID();
    
    GLubyte whiteTexColor[] = { 255, 255, 255, 255 };
    glGenTextures(1, &whiteTex);
    glBindTexture(GL_TEXTURE_2D,whiteTex);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,1,1,0,GL_RGBA,GL_UNSIGNED_BYTE,whiteTexColor);
    
}

void Scene01::render() const{
    glEnable(GL_DEPTH_TEST);
    
    //pass1 record depth ====================================
    glBindFramebuffer(GL_FRAMEBUFFER, shadowFBO);
    
    glClear(GL_DEPTH_BUFFER_BIT);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);

    glUseProgram(recordLightDepthPass->prog);
    recordLightDepthPass->draw();
    glUseProgram(0);
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
    
    //pass2 create shadowmap ====================================
    glBindFramebuffer(GL_FRAMEBUFFER, shadowmapFBO);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    
    glUseProgram(shadowmapPass->prog);
    shadowmapPass->setTextureUniform("ShadowMap", 0, depthTex);
    shadowmapPass->draw();
    glUseProgram(0);
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
    
    //pass3 create g-buffer ====================================
    glBindFramebuffer(GL_FRAMEBUFFER, deferredFBO);
    
    glClear(GL_DEPTH_TEST);
    
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glDisable(GL_DEPTH_TEST);
//    glEnable(GL_DEPTH_TEST);
    
    glUseProgram(gBufferPass->prog);
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    gBufferPass->draw();
    glUseProgram(0);
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
    
    //pass4 shading ====================================
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);
    
    glUseProgram(shadingPass->prog);
    shadowmapPass->setTextureUniform("PositionTex", 0, posTex);
    shadowmapPass->setTextureUniform("NormalTex", 1, normTex);
    shadowmapPass->setTextureUniform("ColorTex", 2, colorTex);
    shadowmapPass->setTextureUniform("ShadowmapTex", 3, unlitColorTex);
    shadingPass->draw();
    glUseProgram(0);
    
}


