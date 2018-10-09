#pragma once
#include "RenderPass.hpp"
class TestRenderViewPass: public RenderPass
{
public:
	TestRenderViewPass();
	void drawPass() override;
	void drawObjects(Object3D *object);
	void init(std::vector<Light*> l, Camera* c, std::vector<Mesh*> m) override;
	~TestRenderViewPass();
};

