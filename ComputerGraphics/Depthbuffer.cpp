#include "Depthbuffer.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <stdexcept>
#include <iostream>
#include <vector>

Depthbuffer::Depthbuffer(){
	framebuffer = 0;
	depthmap = 0;
	resolution = 0;
}

Depthbuffer::~Depthbuffer(){
	glDeleteFramebuffers(1, &framebuffer);
	glDeleteTextures(1, &depthmap);
}

void Depthbuffer::Create(int res){
	resolution = res;

	// Create the fbo
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	// Create the depth texture
	glGenTextures(1, &depthmap);
	BindDepthMap();

	// Texture filter y texture wrap
	// Para el filtro de minificación
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// Para el filtro de magnificación
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER); // S coord
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER); // T coord

	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
		resolution, resolution, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthmap, 0);
	Unbind();
}

void Depthbuffer::Bind(){
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glViewport(0, 0, resolution, resolution);
}

void Depthbuffer::Unbind(){
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Depthbuffer::BindDepthMap(){
	glBindTexture(GL_TEXTURE_2D, depthmap);
}

void Depthbuffer::UnbindDepthMap(){
	glBindTexture(GL_TEXTURE_2D, 0);
}