//
//  ShadowmapPass.cpp
//  Game01
//
//  Created by kazuki sako on 2018/02/07.
//  Copyright © 2018年 kazuki sako. All rights reserved.
//

#include "ShadowmapPass.hpp"
#include "glm/ext.hpp"
#include "../meshes/Mesh.hpp"
#include "../lights/Light.hpp"
#include "../system/defines.h"

ShadowmapPass::ShadowmapPass():RenderPass("shadowPass.vert", "shadowPass.frag"){
	shadowRadius = 10.0f;
	samplesU = 4;
	samplesV = 8;
	jitterMapSize = 8;
	jitterTex = createJitterTex();
}

void ShadowmapPass::init(std::vector<Light*> l, Camera* c, std::vector<Mesh*> m){
    RenderPass::init(l, c, m);
}

void ShadowmapPass::drawObjects(Object3D *mesh, Light *light){
    glUniformMatrix4fv(shadowMatrixLoc, 1, GL_FALSE, &(light->getPVMatrix() * mesh->getModelMatrix())[0][0]);
    mesh->draw(this);
    auto children = mesh->getChildren();
    for(int i=0; i<children.size(); i++){
        drawObjects(children.at(i), light);
    }
}



void ShadowmapPass::drawPass(){
    viewMatrix = camera->viewMatrix;
    projectionMatrix = camera->projectionMatrix;

	setTextureUniform("OffsetTex", 1, jitterTex);
	setUniform("Radius", shadowRadius / 512.0f);
	setUniform("OffsetTexSize", glm::vec3(jitterMapSize, jitterMapSize, samplesU * samplesV / 2.0f));


	setUniform("ViewMatrix", viewMatrix);
    
    //シャドウマップ生成に使うライトは1つだけ。castshadow=trueにしたものにする。
    Light *light = lights[0];
    for(int i=0; i<lights.size(); i++){
        if(lights[i]->castShadow == true){
            light = lights[i];
			//std::cout << glm::to_string(light->getPosition() * -1) << std::endl;
			glm::vec3 lightdir = glm::normalize(light->getPosition());
			setUniform("WorldLightDirection", lightdir);
            break;
        }
    }
    
    for(int i=0; i<meshes.size(); i++){
        drawObjects(meshes[i], light);
    }    
}

// Return random float between -0.5 and 0.5
float ShadowmapPass::jitter()const {
	return ((float)rand() / RAND_MAX) - 0.5f;
}

GLuint ShadowmapPass::createJitterTex() const {
	int radius = shadowRadius;

	int size = jitterMapSize;
	int samples = samplesU * samplesV;
	int bufSize = size * size * samples * 2;
	float *data = new float[bufSize];

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			for (int k = 0; k < samples; k += 2) {
				int x1, y1, x2, y2;
				x1 = k % (samplesU);
				y1 = (samples - 1 - k) / samplesU;
				x2 = (k + 1) % samplesU;
				y2 = (samples - 1 - k - 1) / samplesU;

				glm::vec4 v;
				v.x = (x1 + 0.5f) + jitter();
				v.y = (x1 + 0.5f) + jitter();
				v.z = (x2 + 0.5f) + jitter();
				v.w = (y2 + 0.5f) + jitter();

				v.x /= samplesU;
				v.y /= samplesV;
				v.z /= samplesU;
				v.w /= samplesV;

				int cell = ((k / 2) * size * size + j * size + i) * 4;
				data[cell + 0] = sqrtf(v.y) * cosf(TWOPI * v.x);
				data[cell + 1] = sqrtf(v.y) * sinf(TWOPI * v.x);
				data[cell + 2] = sqrtf(v.w) * cosf(TWOPI * v.z);
				data[cell + 3] = sqrtf(v.w) * sinf(TWOPI * v.z);
			}
		}

	}

	GLuint tex;
	glGenTextures(1, &tex);
	glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA32F, size, size, samples / 2, 0, GL_RGBA, GL_FLOAT, data);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	delete[] data;
	return tex;

}


