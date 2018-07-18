#include "TestPass.h"



TestPass::TestPass():RenderPass("simple.vert", "simple.frag")
{
	quad = new QuadScreenMesh();
}

void TestPass::init(std::vector<Light*> l, Camera* c, std::vector<Mesh*> m) {
	RenderPass::init(l, c, m);
	viewMatrix = glm::mat4(1);
	projectionMatrix = glm::mat4(1);
}

void TestPass::drawPass() {
	quad->draw(this);
}

TestPass::~TestPass()
{

	
}
