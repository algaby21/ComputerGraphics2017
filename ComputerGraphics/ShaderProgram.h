/*********************************************************
Materia: Gráficas Computacionales
Fecha: 2 de octubre del 2017
Autor: A01169073 Aldo A. Reyna Gómez
*********************************************************/

#pragma once
#include "Shader.h"
#include <string>
#include <memory>

using namespace std;

class ShaderProgram {
public:
	ShaderProgram();
	~ShaderProgram();
	void CreateProgram();
	void AttachShader(string path, GLenum type);
	void LinkProgram();
	void Activate();
	void Deactivate();
	void SetAttribute(GLuint locationIndex, string name);
	void SetUniform(string name, float value);
	void SetUniform(string name, float x, float y);
	void SetUniform(string name, float x, float y, float z);
	void SetUniform(string name, float x, float y, float z, float w);
	void SetUniformMatrix(string name, mat4 matrix);
	void SetUniformMatrix(string name, mat3 matrix);
	void SetUniformVec(string name, vec3 vec);

private:
	void DeleteAndDetachShaders();
	void DeleteProgram();
	GLuint _programHandle;
	vector<unique_ptr<Shader>> _attachedShaders;
};