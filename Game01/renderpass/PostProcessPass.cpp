#include "PostProcessPass.h"
#include "../system/defines.h"


PostProcessPass::PostProcessPass()
	:RenderPass("ppTest.vert", "ppTest.frag")
{
	quad = new QuadScreenMesh();


	for (int i = 0; i < passNum-1; i++) {
		glGenFramebuffers(1, &fbos[i]);
		glBindFramebuffer(GL_FRAMEBUFFER, fbos[i]);

		glGenRenderbuffers(1, &colorBufs[i]);
		glBindRenderbuffer(GL_RENDERBUFFER, colorBufs[i]);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, colorBufs[i]);

		glGenTextures(1, &fboTexes[i]);
		glBindTexture(GL_TEXTURE_2D, fboTexes[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, WINDOW_W, WINDOW_H, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fboTexes[i], 0);

		GLenum drawBuffers[] = { GL_NONE, GL_COLOR_ATTACHMENT0 };
		glDrawBuffers(2, drawBuffers);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

	}
}



void PostProcessPass::drawPass(GLuint prevPassTex) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

	viewMatrix = glm::mat4(1);
	projectionMatrix = glm::mat4(1);

	for (int i = 0; i < passNum; i++) {
		if (i == 0) {
			setTextureUniform("MainTex", 0, prevPassTex);
		}
		else {
			setTextureUniform("MainTex", 0, fboTexes[i - 1]);
		}

		bool useFrameBuffer = (i != (passNum - 1));
		if (useFrameBuffer) glBindFramebuffer(GL_FRAMEBUFFER, fbos[i]);
		
		glUseProgram(prog);
		std::string passName = "pass" + std::to_string(i);

		setFragmentSubRoutine(passName.c_str());

		quad->draw(this);
		glUseProgram(0);

		if (useFrameBuffer) glBindFramebuffer(GL_FRAMEBUFFER, 0);

	}

	
}




PostProcessPass::~PostProcessPass()
{
}
