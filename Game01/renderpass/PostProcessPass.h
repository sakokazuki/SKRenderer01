#pragma once

#include "RenderPass.hpp"
#include "../meshes/QuadScreenMesh.hpp"


class PostProcessPass: public RenderPass
{
private:
	Mesh * quad;
	static const int passNum = 2;
public:
	GLuint fbos[passNum - 1];
	GLuint colorBufs[passNum - 1];
	GLuint fboTexes[passNum - 1];
	PostProcessPass();
	void drawPass(GLuint prevPassTex) override;
	
	~PostProcessPass();
};

