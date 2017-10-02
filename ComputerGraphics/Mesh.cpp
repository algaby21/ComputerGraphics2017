/*********************************************************
Materia: Gráficas Computacionales
Fecha: 2 de octubre del 2017
Autor: A01169073 Aldo A. Reyna Gómez
*********************************************************/

#include "Mesh.h"

Mesh::Mesh(){
	// Inicializa los valores por default de las variables.
	vao = 0;
	positionsVBO = 0;
	colorsVBO = 0;
	_vertexCount = 0;
}

Mesh::~Mesh(){
	// Borra el VAO y todos los VBOs.
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &positionsVBO);
	glDeleteBuffers(1, &colorsVBO);
}

void Mesh::CreateMesh(GLint vertexCount){
	// Inicializa la variable _vertexCount.
	// Crea un VAO y guarda su identificador en la variable vao.
	_vertexCount = vertexCount;
	glGenVertexArrays(1, &vao);
}

void Mesh::Draw(GLenum primitive){
	// Hace bind del VAO y dibuja todos los vértices de la malla poligonal
	// utilizando las variables	primitive y _vertexCount
	glBindVertexArray(vao);
	glDrawArrays(primitive, 0, _vertexCount);
	// Desactivamos el manager
	glBindVertexArray(0);
}

void Mesh::SetPositionAttribute(vector<vec2> positions, GLenum usage, GLuint locationIndex){
	if (positions.empty() || positions.size()!=_vertexCount) {
		return;
	}
	SetAttributeData(positionsVBO, sizeof(vec2)*positions.size(), positions.data(), usage, locationIndex, 2);
}

void Mesh::SetPositionAttribute(vector<vec3> positions, GLenum usage, GLuint locationIndex){
	if (positions.empty() || positions.size() != _vertexCount) {
		return;
	}
	SetAttributeData(positionsVBO, sizeof(vec3)*positions.size(), positions.data(), usage, locationIndex, 3);
}

void Mesh::SetColorAttribute(vector<vec3> colors, GLenum usage, GLuint locationIndex){
	if (colors.empty() || colors.size() != _vertexCount) {
		return;
	}
	SetAttributeData(positionsVBO, sizeof(vec3)*colors.size(), colors.data(), usage, locationIndex, 3);
}

void Mesh::SetColorAttribute(vector<vec4> colors, GLenum usage, GLuint locationIndex){
	if (colors.empty() || colors.size() != _vertexCount) {
		return;
	}
	SetAttributeData(positionsVBO, sizeof(vec4)*colors.size(), colors.data(), usage, locationIndex, 4);
}

void Mesh::SetAttributeData(GLuint &buffer, const GLsizeiptr size, const void* data, GLenum usage, GLuint locationIndex, const GLint components){
	// Encargado de crear un nuevo VBO con los datos proporcionados.
	// Si el buffer ya ha sido creado antes, primero se borra y luego se genera uno nuevo.
	if (buffer != 0) {
		glDeleteBuffers(1, &buffer);
	}
	glBindVertexArray(vao);
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, size, data, usage);
	glEnableVertexAttribArray(locationIndex);
	glVertexAttribPointer(locationIndex, components, GL_FLOAT, GL_FALSE, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}