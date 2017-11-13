/*********************************************************
Materia: Gráficas Computacionales
Fecha: 2 de octubre del 2017
Autor: A01169073 Aldo A. Reyna Gómez
*********************************************************/

#include "ShaderProgram.h"
#include "Shader.h"
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include <iostream>
using namespace std;

ShaderProgram::ShaderProgram() {
	// Inicializa los valores por default de las variables.
	_programHandle = 0;
}

ShaderProgram::~ShaderProgram(){
	// Manda a llamar el método DeleteProgram().
	DeleteProgram();
}

void ShaderProgram::CreateProgram(){
	// Crea el programa shader y guarda un identificador del programa creado en _programHandle.
	_programHandle = glCreateProgram();
}

void ShaderProgram::AttachShader(string path, GLenum type){
	// Crea y agrega los shaders a una nueva lista.
	unique_ptr<Shader> shader(new Shader);
	shader->CreateShader(path, type);
	_attachedShaders.push_back(move(shader));
}

void ShaderProgram::LinkProgram(){
	// Adjunta los shaders en la lista _attachedShaders al programa shader.
	// Inicia el proceso de linkeo.
	// Manda a llamar al método DeleteAndDetachShaders().
	for (auto const& s : _attachedShaders) {
		glAttachShader(_programHandle, s.get()->GetHandle());
	}
	
	/*for (int i = 0; i < _attachedShaders.size(); i++) {
		glAttachShader(_programHandle, _attachedShaders[i].get()->GetHandle());
	}*/
	glLinkProgram(_programHandle);

	// Get status
	GLint linkSuccess = 0;
	glGetProgramiv(_programHandle, GL_LINK_STATUS, &linkSuccess);
	if (linkSuccess == GL_FALSE)	{
		// Get link log length
		GLint logLength = 0;
		glGetProgramiv(_programHandle, GL_INFO_LOG_LENGTH, &logLength);

		if (logLength > 0)		{
			// Allocate memory for link log
			std::vector<GLchar> linkLog(logLength);

			// Get link log
			glGetProgramInfoLog(_programHandle, logLength, &logLength, &linkLog[0]);

			// Print link log
			for (size_t i = 0; i < linkLog.size(); i++)
				cout << linkLog[i];
			cout << std::endl;
		}
		cout << "Shaders could not be linked." << std::endl;

		// Delete and detach shaders; delte program handle
		DeleteProgram();

		return;
	}

	cout << "Build succeeded... " << endl;
	DeleteAndDetachShaders();
}

void ShaderProgram::Activate(){
	// Activamos el manager del program shader.
	glUseProgram(_programHandle);
}

void ShaderProgram::Deactivate(){
	// Desactivamos el manager del programa shader.
	glUseProgram(0);
}

void ShaderProgram::SetAttribute(GLuint locationIndex, string name){
	// Hace la relación entre el índice en el shader de un VBO y el nombre de la variable.
	glBindAttribLocation(_programHandle, locationIndex, name.c_str());
}

void ShaderProgram::SetUniformi(string name, int value) {
	GLint uniformLocation = glGetUniformLocation(_programHandle, name.c_str());
	glUniform1i(uniformLocation, value);;
}

void ShaderProgram::SetUniform(string name, float value){
	// Encuentra la posición de la variable en el shader y le da el valor correcto.
	GLint uniformLocation = glGetUniformLocation(_programHandle, name.c_str());
	glUniform1f(uniformLocation, value);;
}

void ShaderProgram::SetUniform(string name, float x, float y){
	GLint uniformLocation = glGetUniformLocation(_programHandle, name.c_str());
	glUniform2f(uniformLocation, x, y);
}

void ShaderProgram::SetUniform(string name, float x, float y, float z){
	GLint uniformLocation = glGetUniformLocation(_programHandle, name.c_str());
	glUniform3f(uniformLocation, x, y, z);
}

void ShaderProgram::SetUniform(string name, float x, float y, float z, float w){
	GLint uniformLocation = glGetUniformLocation(_programHandle, name.c_str());
	glUniform4f(uniformLocation, x, y, z, w);
}

void ShaderProgram::SetUniformMatrix(string name, mat4 matrix){
	GLint uniformLocation = glGetUniformLocation(_programHandle, name.c_str());
	glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, value_ptr(matrix));
}

void ShaderProgram::SetUniformMatrix(string name, mat3 matrix) {
	GLint uniformLocation = glGetUniformLocation(_programHandle, name.c_str());
	glUniformMatrix3fv(uniformLocation, 1, GL_FALSE, value_ptr(matrix));
}

void ShaderProgram::SetUniformVec(string name, vec3 vec){
	GLint uniformLocation = glGetUniformLocation(_programHandle, name.c_str());
	glUniform3fv(uniformLocation, 1, &vec[0]);
}

void ShaderProgram::DeleteAndDetachShaders() {
	for (auto const& s : _attachedShaders) {
		glDetachShader(_programHandle, s.get()->GetHandle());
	}
	/*for (int i = 0; i < _attachedShaders.size(); i++) {
		glDetachShader(_programHandle, _attachedShaders[i].get()->GetHandle());
	}*/
	_attachedShaders.clear();
}

void ShaderProgram::DeleteProgram(){
	DeleteAndDetachShaders();
	glDeleteProgram(_programHandle);
}
