/*********************************************************
Materia: Gráficas Computacionales
Fecha: 2 de octubre del 2017
Autor: A01169073 Aldo A. Reyna Gómez
*********************************************************/

#include "Shader.h"
#include "InputFile.h"

Shader::Shader() {
	// Inicializa los valores por default de las variables.
	_shaderHandle = 0;
}

Shader::~Shader() {
	// Borra el shader representado por la variable _shaderHandle.
	glDeleteShader(_shaderHandle);
}

void Shader::CreateShader(string path, GLenum type) {
	// Carga el código, crea y compila un archivo shader.
	// Utiliza path para abrir un archivo y obtener el código fuente del shader.
	// Crea un nuevo shader del tipo type y guarda su identificador en _shaderHandle.
	// Si ya ha sido cargado un shader antes, primero se borra y luego se genera uno nuevo.
	if (_shaderHandle) glDeleteShader(_shaderHandle);
	InputFile myfile;
	myfile.Read(path);
	string source = myfile.GetContents();
	_shaderHandle = glCreateShader(type);
	const GLchar *source_c = (const GLchar*)source.c_str();
	// Continuar leyendo hasta que encuentre un nullptr.
	glShaderSource(_shaderHandle, 1, &source_c, nullptr);
	glCompileShader(_shaderHandle);
}

GLuint Shader::GetHandle() {
	// Regresa el valor de la variable _shaderHandle.
	return _shaderHandle;
}
