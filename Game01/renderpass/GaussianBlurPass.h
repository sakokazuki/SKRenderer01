
#ifndef GaussianBlurPass_h
#define GaussianBlurPass_h

#include <stdio.h>

#include "RenderPass.hpp"
#include "../meshes/QuadScreenMesh.hpp"

class GaussianBlurPass :public RenderPass {
private:
	Mesh * quad;
public:
	GaussianBlurPass();
	void drawPass() override;
	void drawObjects(Object3D *object);
	void init(std::vector<Light*> l, Camera* c, std::vector<Mesh*> m) override;
};

#endif /* GaussianBlurPass_h */
