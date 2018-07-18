#include "TestApp2.h"

namespace app{
	TestApp2::TestApp2(Window *window): app::AppBase(window)
	{
		const GLfloat *const size(window->getSize());
		int windowW = size[0];
		int windowH = size[1];
		Renderer* renderer = new TestRenderer(windowW, windowH);
		Scene::Scene* scene = new Scene::Scene();

		setRenderer(renderer);
		setScene(scene);
	}

	void TestApp2::loop() {
		AppBase::loop();
	}



	TestApp2::~TestApp2()
	{
	}

}


