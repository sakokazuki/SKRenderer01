#include "TestRenderViewPass.h"
#include "../meshes/Mesh.hpp"
#include "../lights/Light.hpp"


TestRenderViewPass::TestRenderViewPass():RenderPass("simple.vert", "simple.frag")
{
		
}


void TestRenderViewPass::init(std::vector<Light*> l, Camera* c, std::vector<Mesh*> m) {
	RenderPass::init(l, c, m);

}

void TestRenderViewPass::drawObjects(Object3D* mesh) {
	mesh->draw(this);
	auto children = mesh->getChildren();
	for (int i = 0; i < children.size(); i++) {
		drawObjects(children.at(i));
	}
}

void TestRenderViewPass::drawPass() {
	viewMatrix = camera->viewMatrix;
	projectionMatrix = camera->projectionMatrix;
	for (int i = 0; i < meshes.size(); i++) {
		drawObjects(meshes[i]);
	}
}



TestRenderViewPass::~TestRenderViewPass()
{
}
