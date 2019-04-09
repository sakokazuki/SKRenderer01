//
//  ShadowmapPass.cpp
//  Game01
//
//  Created by kazuki sako on 2018/02/07.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#include "GaussianBlurPass.h"
#include "glm/ext.hpp"
#include "../meshes/Mesh.hpp"
#include "../lights/Light.hpp"
#include "../system/defines.h"

GaussianBlurPass::GaussianBlurPass() :RenderPass("gaussianFilter.vert", "gaussianFilter.frag") {
	quad = new QuadScreenMesh();
}

void GaussianBlurPass::init(std::vector<Light*> l, Camera* c, std::vector<Mesh*> m) {
	RenderPass::init(l, c, m);
	viewMatrix = glm::mat4(1);
	projectionMatrix = glm::mat4(1);
}

void GaussianBlurPass::drawObjects(Object3D *mesh) {
	mesh->draw(this);
	auto children = mesh->getChildren();
	for (int i = 0; i<children.size(); i++) {
		drawObjects(children.at(i));
	}
}



void GaussianBlurPass::drawPass() {
	quad->draw(this);
}

