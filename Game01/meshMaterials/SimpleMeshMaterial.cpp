
#include "SimpleMeshMaterial.h"

SimpleMeshMaterial::SimpleMeshMaterial() {
	

}

void SimpleMeshMaterial::setUniforms(RenderPass* renderPass) {
	renderPass->setUniform("Color", glm::vec3(1.0f, 0.0f, 1.0f));
}

SimpleMeshMaterial::~SimpleMeshMaterial() {

}
