/*********************************************************
Materia: Gráficas Computacionales
Fecha: 2 de octubre del 2017
Autor: A01169073 Aldo A. Reyna Gómez
*********************************************************/

#pragma once
#include <string>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector>
#include <glm/glm.hpp>

using namespace std;
using namespace glm;

class Shader {
public:
	Shader();
	~Shader();
	void CreateShader(string path, GLenum type);
	GLuint GetHandle();

private:
	GLuint _shaderHandle;
};