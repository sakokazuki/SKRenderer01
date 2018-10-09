#pragma once


#include <stdio.h>

#include "MeshMaterial.hpp"

class SimpleMeshMaterial :public MeshMaterial {
private:

public:
	SimpleMeshMaterial();
	void setUniforms(RenderPass* renderPass) override;
	~SimpleMeshMaterial();
};