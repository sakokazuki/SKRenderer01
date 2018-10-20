#include "PostProcessingRenderer.h"



PostProcessingRenderer::PostProcessingRenderer()
{
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_RENDERBUFFER, fbo);


}


PostProcessingRenderer::~PostProcessingRenderer()
{
}
