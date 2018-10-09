#include "TestRenderer.h"



TestRenderer::TestRenderer(int ww, int wh): Renderer(ww, wh)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	testPass = new TestPass();
	testRenderViewPass = new TestRenderViewPass();
}

void TestRenderer::render(Scene::Scene* scene) const {
	Renderer::render(scene);

	scene->update();
	auto lights = scene->getLights();
	auto meshes = scene->getMehses();
	auto camera = scene->getCamera();

	testPass->init(lights, camera, meshes);
	testRenderViewPass->init(lights, camera, meshes);



	/*glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

	glUseProgram(testPass->prog);

	testPass->drawPass();

	glUseProgram(0);*/

	glEnable(GL_CULL_FACE | GL_DEPTH_TEST);
	glUseProgram(testRenderViewPass->prog);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	testRenderViewPass->drawPass();

	glUseProgram(0);


}


TestRenderer::~TestRenderer()
{
}
