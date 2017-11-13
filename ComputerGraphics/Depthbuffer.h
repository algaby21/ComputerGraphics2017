/*********************************************************
Materia: Gráficas Computacionales
Fecha: 30 de octubre de 2017
Autor: A01169073 Aldo A. Reyna Gómez,
	   A01133890 Gabriela A. Lugo
*********************************************************/

#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>

using namespace std;
using namespace glm;

class Depthbuffer {
public:
	Depthbuffer();
	~Depthbuffer();
	void Create(int res);
	void Bind();
	void Unbind();
	void BindDepthMap();
	void UnbindDepthMap();

private:
	GLuint framebuffer;
	GLuint depthmap;
	GLsizei resolution;
};