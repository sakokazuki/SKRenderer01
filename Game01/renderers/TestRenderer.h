#pragma once
#include "./Renderer.hpp"
#include "../renderpass/TestPass.h"


class TestRenderer : public Renderer
{
private:
	RenderPass * testPass;
public:
	TestRenderer(int ww, int wh);
	void render(Scene::Scene* scene) const override;
	~TestRenderer();
};

