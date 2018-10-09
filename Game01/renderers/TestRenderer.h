#pragma once
#include "./Renderer.hpp"
#include "../renderpass/TestPass.h"
#include "../renderpass/TestRenderViewPass.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include "../system/ShaderFunc.hpp"

class TestRenderer : public Renderer
{
private:
	RenderPass * testPass;
	RenderPass * testRenderViewPass;
public:
	TestRenderer(int ww, int wh);
	GLuint prog;

	void render(Scene::Scene* scene) const override;
	~TestRenderer();
};

