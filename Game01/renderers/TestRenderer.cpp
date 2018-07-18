#include "TestRenderer.h"


TestRenderer::TestRenderer(int ww, int wh): Renderer(ww, wh)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	testPass = new TestPass();
}

void TestRenderer::render(Scene::Scene* scene) const {
	Renderer::render(scene);

	scene->update();
	auto lights = scene->getLights();
	auto meshes = scene->getMehses();
	auto camera = scene->getCamera();

	testPass->init(lights, camera, meshes);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE | GL_DEPTH_TEST);
	glCullFace(GL_BACK);

	glUseProgram(testPass->prog);

	testPass->drawPass();

	glUseProgram(0);


}


TestRenderer::~TestRenderer()
{
}
