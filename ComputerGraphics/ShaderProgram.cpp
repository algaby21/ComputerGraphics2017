/*********************************************************
Materia: Gráficas Computacionales
Fecha: 2 de octubre del 2017
Autor: A01169073 Aldo A. Reyna Gómez
*********************************************************/

#include "ShaderProgram.h"
#include "Shader.h"
#include <memory>
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

void ShaderProgram::SetUniform(string name, float value){
	// Encuentra la posición de la variable en el shader y le da el valor correcto.
	Activate();
	GLint uniformLocation = glGetUniformLocation(_programHandle, name.c_str());
	glUniform1f(uniformLocation, value);
	Deactivate();
}

void ShaderProgram::SetUniform(string name, float x, float y){
	Activate();
	GLint uniformLocation = glGetUniformLocation(_programHandle, name.c_str());
	glUniform2f(uniformLocation, x, y);
	Deactivate();
}

void ShaderProgram::SetUniform(string name, float x, float y, float z){
	Activate();
	GLint uniformLocation = glGetUniformLocation(_programHandle, name.c_str());
	glUniform3f(uniformLocation, x, y, z);
	Deactivate();
}

void ShaderProgram::SetUniform(string name, float x, float y, float z, float w){
	Activate();
	GLint uniformLocation = glGetUniformLocation(_programHandle, name.c_str());
	glUniform4f(uniformLocation, x, y, z, w);
	Deactivate();
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
