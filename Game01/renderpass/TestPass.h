#pragma once

#include "../renderpass/RenderPass.hpp"
#include "../meshes/QuadScreenMesh.hpp"

class TestPass:public RenderPass
{
private:
	Mesh* quad;
public:
	TestPass();
	void drawPass() override;
	void init(std::vector<Light*> l, Camera* c, std::vector<Mesh*> m) override;
	~TestPass();
};

