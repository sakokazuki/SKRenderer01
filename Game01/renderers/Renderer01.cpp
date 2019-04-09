//
//  Renderer01.cpp
//  Game01
//
//  Created by kazuki sako on 2018/02/07.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#include "Renderer01.hpp"



Renderer01::Renderer01(int ww, int wh):Renderer(ww, wh){
    glClearColor(1.0f,1.0f,1.0f,1.0f);
    
    shadowmapPass = new ShadowmapPass();
	gaussianBlurPass = new GaussianBlurPass();
    recordLightDepthPass = new RecordLightDepthPass();
    gBufferPass = new GBufferPass();
    shadingPass = new PbrShadingPass();
	testPass = new TestPass();
	postProcessPass = new PostProcessPass();

	shadowColor = glm::vec3(0.3, 0.3, 0.3);
	shadowSoftness = 2.0;
	shadowBleedRedutionAmount = 0.2;
	minShadowVarriance = 0.00001;

    
    //FBO 1 -----------------------------------------------------------

	glGenFramebuffers(1, &shadowFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, shadowFBO);

	glGenRenderbuffers(1, &lightDepthBuf);
	glBindRenderbuffer(GL_RENDERBUFFER, lightDepthBuf);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, windowW, windowH);

	glGenTextures(1, &depthColorTex);
	glBindTexture(GL_TEXTURE_2D, depthColorTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RG32F, windowW, windowH, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, lightDepthBuf);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, depthColorTex, 0);
    
    GLenum drawBuffers[] = {GL_NONE, GL_COLOR_ATTACHMENT0};
    glDrawBuffers(2, drawBuffers);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//FBO 1.5 -----------------------------------------------------------
	glGenFramebuffers(1, &shadowFilterFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, shadowFilterFBO);

	glGenTextures(1, &tmpDepthColorTex);
	glBindTexture(GL_TEXTURE_2D, tmpDepthColorTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, windowW, windowH, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tmpDepthColorTex, 0);
	GLenum drawbuffer2_5[] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, drawbuffer2_5);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
    //FBO 2 -----------------------------------------------------------
    glGenFramebuffers(1, &shadowmapFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, shadowmapFBO);
    
    glGenRenderbuffers(1, &shadowDepthBuf);
    glBindRenderbuffer(GL_RENDERBUFFER, shadowDepthBuf);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, windowW, windowH);
    
    glGenTextures(1, &shadowColorTex);
    glBindTexture(GL_TEXTURE_2D, shadowColorTex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, windowW, windowH, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, shadowDepthBuf);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, shadowColorTex, 0);
    
    GLenum drawbuffers2[] = {GL_NONE, GL_COLOR_ATTACHMENT0};
    glDrawBuffers(2, drawbuffers2);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    
    //FBO 3 -----------------------------------------------------------
    glGenFramebuffers(1, &deferredFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, deferredFBO);
    
    glGenRenderbuffers(1, &depthBuf);
    glBindRenderbuffer(GL_RENDERBUFFER, depthBuf);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, windowW, windowH);
    
    glGenTextures(1, &posTex);
    glBindTexture(GL_TEXTURE_2D, posTex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, windowW, windowH, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    glGenTextures(1, &normTex);
    glBindTexture(GL_TEXTURE_2D, normTex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, windowW, windowH, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   

    glGenTextures(1, &colorTex);
    glBindTexture(GL_TEXTURE_2D, colorTex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, windowW, windowH, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuf);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, posTex, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, normTex, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, colorTex, 0);
    
    GLenum drawBuffers3[] = {GL_NONE, GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2};
    glDrawBuffers(4, drawBuffers3);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);



	glGenFramebuffers(1, &defferedFbo);
	glBindFramebuffer(GL_FRAMEBUFFER, defferedFbo);

	glGenRenderbuffers(1, &defferedColorBuf);
	glBindRenderbuffer(GL_RENDERBUFFER, defferedColorBuf);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, defferedColorBuf);

	glGenTextures(1, &defferedFboTex);
	glBindTexture(GL_TEXTURE_2D, defferedFboTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, windowW, windowH, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, defferedFboTex, 0);

	GLenum defferedDrawBuffers[] = { GL_NONE, GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(2, defferedDrawBuffers);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

    
    GLubyte whiteTexColor[] = { 255, 255, 255, 255 };
    glGenTextures(1, &whiteTex);
    glBindTexture(GL_TEXTURE_2D,whiteTex);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,1,1,0,GL_RGBA,GL_UNSIGNED_BYTE,whiteTexColor);
       
}

void Renderer01::render(Scene::Scene* scene) const{
    Renderer::render(scene);
    
    scene->update();
    auto lights = scene->getLights();
    auto meshes = scene->getMehses();
    auto camera = scene->getCamera();
    
    shadowmapPass->init(lights, camera, meshes);
	gaussianBlurPass->init(lights, camera, meshes);
    recordLightDepthPass->init(lights, camera, meshes);
    gBufferPass->init(lights, camera, meshes);
    shadingPass->init(lights, camera, meshes);
	testPass->init(lights, camera, meshes);
    
    glEnable(GL_DEPTH_TEST);

    //pass1 record depth ====================================
    glBindFramebuffer(GL_FRAMEBUFFER, shadowFBO);
    
    //glClear(GL_DEPTH_BUFFER_BIT);
    glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glUseProgram(recordLightDepthPass->prog);
    recordLightDepthPass->drawPass();
    glUseProgram(0);
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//pass1.5 gaussian blur shadowmap(X) ====================================
	glBindFramebuffer(GL_FRAMEBUFFER, shadowFilterFBO);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

	glUseProgram(gaussianBlurPass->prog);
	gaussianBlurPass->setTextureUniform("ShadowMap", 0, depthColorTex);
	gaussianBlurPass->setUniform("BlurScale", glm::vec2(shadowSoftness*1.0/(float)windowW, 0.0));
	gaussianBlurPass->drawPass();
	glUseProgram(0);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//pass1.5 gaussian blur shadowmap(Y) ====================================
	glBindFramebuffer(GL_FRAMEBUFFER, shadowFBO);

	glUseProgram(gaussianBlurPass->prog);
	gaussianBlurPass->setTextureUniform("ShadowMap", 0, tmpDepthColorTex);
	gaussianBlurPass->setUniform("BlurScale", glm::vec2(0.0, shadowSoftness*1.0 / (float)windowH));
	gaussianBlurPass->drawPass();
	glUseProgram(0);


	glBindFramebuffer(GL_FRAMEBUFFER, 0);


    
    //pass2 create shadowmap ====================================
    glBindFramebuffer(GL_FRAMEBUFFER, shadowmapFBO);
    
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glUseProgram(shadowmapPass->prog);
	shadowmapPass->setUniform("MinShadowVariance", minShadowVarriance);
	shadowmapPass->setUniform("ShadowBleedRedutionAmount", shadowBleedRedutionAmount);
	shadowmapPass->setUniform("ShadowColor", shadowColor);
    shadowmapPass->setTextureUniform("ShadowMap", 0, depthColorTex);
    shadowmapPass->drawPass();
    glUseProgram(0);
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
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
	//glBindFramebuffer(GL_FRAMEBUFFER, defferedFbo);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    
    glUseProgram(shadingPass->prog);
    
    shadingPass->setTextureUniform("PositionTex", 0, posTex);
    shadingPass->setTextureUniform("NormalTex", 1, normTex);
    shadingPass->setTextureUniform("ColorTex", 2, colorTex);
    shadingPass->setTextureUniform("ShadowmapTex", 3, shadowColorTex);
    shadingPass->drawPass();
    glUseProgram(0);
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//postProcessPass->drawPass(defferedFboTex);
	
   
}


