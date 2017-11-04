/*********************************************************
Materia: Gráficas Computacionales
Fecha: 30 de octubre de 2017
Autor: A01169073 Aldo A. Reyna Gómez
*********************************************************/

#pragma once
#include <IL/il.h>
#include <string>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector>
#include <glm/glm.hpp>

using namespace std;
using namespace glm;

class Texture2D {
public:
	Texture2D();
	~Texture2D();
	void LoadTexture(string path);
	void Bind();
	void Unbind();

private:
	GLuint textureID;
};