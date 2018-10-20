#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/ext.hpp>
#include <GL/glew.h>

class PostProcessingRenderer
{
private:
	GLuint fbo;
public:
	PostProcessingRenderer();
	~PostProcessingRenderer();
};

