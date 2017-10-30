/*********************************************************
Materia: Gráficas Computacionales
Fecha: 2 de octubre del 2017
Autor: A01169073 Aldo A. Reyna Gómez
*********************************************************/

#include "Mesh.h"
using namespace std;

Mesh::Mesh(){
	// Inicializa los valores por default de las variables.
	vao = 0;
	positionsVBO = 0;
	colorsVBO = 0;
	indicesBO = 0;
	normalVBO = 0;
	_vertexCount = 0;
	_indicesCount = 0;
}

Mesh::~Mesh(){
	// Borra el VAO y todos los VBOs.
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &positionsVBO);
	glDeleteBuffers(1, &colorsVBO);
	glDeleteBuffers(1, &indicesBO);
	glDeleteBuffers(1, &normalVBO);
	_vertexCount = 0;
	//_indicesCount = 0;
}

void Mesh::CreateMesh(GLint vertexCount){
	// Inicializa la variable _vertexCount.
	// Crea un VAO y guarda su identificador en la variable vao.
	glGenVertexArrays(1, &vao);
	_vertexCount = vertexCount;
}

void Mesh::Draw(GLenum primitive){
	// Hace bind del VAO y dibuja todos los vértices de la malla poligonal
	// utilizando las variables	primitive y _vertexCount
	glBindVertexArray(vao);
	if (_indicesCount > 0)
		glDrawElements(primitive, _indicesCount, GL_UNSIGNED_INT, nullptr);
	else
		glDrawArrays(primitive, 0, _vertexCount);	
	// Desactivamos el manager
	glBindVertexArray(0);
}

void Mesh::SetPositionAttribute(vector<vec2> positions, GLenum usage, GLuint locationIndex){
	if (positions.size() > 0 && positions.size() == _vertexCount)
		SetAttributeData(positionsVBO, sizeof(vec2)*positions.size(), positions.data(), usage, locationIndex, 2);
}

void Mesh::SetPositionAttribute(vector<vec3> positions, GLenum usage, GLuint locationIndex){
	if (positions.size() > 0 && positions.size() == _vertexCount)
		SetAttributeData(positionsVBO, sizeof(vec3)*positions.size(), positions.data(), usage, locationIndex, 3);
}

void Mesh::SetColorAttribute(vector<vec3> colors, GLenum usage, GLuint locationIndex){
	if (colors.size() > 0 && colors.size() == _vertexCount)
		SetAttributeData(positionsVBO, sizeof(vec3)*colors.size(), colors.data(), usage, locationIndex, 3);
}

void Mesh::SetColorAttribute(vector<vec4> colors, GLenum usage, GLuint locationIndex){
	if (colors.size() > 0 && colors.size() == _vertexCount)
		SetAttributeData(positionsVBO, sizeof(vec4)*colors.size(), colors.data(), usage, locationIndex, 4);
}

void Mesh::SetNormalAttribute(vector<vec3> normal, GLenum usage, GLuint locationIndex){
	if (normal.size() > 0 && normal.size() == _vertexCount)
		SetAttributeData(normalVBO, sizeof(vec3)*normal.size(), normal.data(), usage, locationIndex, 3);
}

void Mesh::SetIndices(vector<unsigned int> indices, GLenum usage) {
	if (indices.size() > 0) {
		_indicesCount = indices.size();
		if (indicesBO) glDeleteBuffers(1, &indicesBO);
		glBindVertexArray(vao);
		glGenBuffers(1, &indicesBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GL_UNSIGNED_INT)*indices.size(), indices.data(), usage);
		glBindVertexArray(0);
	}
}

void Mesh::SetAttributeData(GLuint &buffer, const GLsizeiptr size, const void* data, GLenum usage, GLuint locationIndex, const GLint components){
	// Encargado de crear un nuevo VBO con los datos proporcionados.
	// Si el buffer ya ha sido creado antes, primero se borra y luego se genera uno nuevo.
	if (buffer)	glDeleteBuffers(1, &buffer);
	glBindVertexArray(vao);
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, size, data, usage);
	glEnableVertexAttribArray(locationIndex);
	glVertexAttribPointer(locationIndex, components, GL_FLOAT, GL_FALSE, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}