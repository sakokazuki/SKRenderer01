#pragma once
#include <stdio.h>
#include "../renderers/TestRenderer.h"
#include "../scenes/Scene.hpp"
#include "./AppBase.hpp"

namespace app {
	class TestApp2 : public AppBase {
	public:
		TestApp2(Window* window);
		void loop() override;
		~TestApp2();
	};
}

