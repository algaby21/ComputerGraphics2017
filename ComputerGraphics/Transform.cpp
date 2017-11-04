#include "Transform.h"

using namespace glm;
using namespace std;

Transform::Transform(){
	_position = vec3(0.0f, 0.0f, 0.0f);
	_rotation = quat(vec3(0.0f, 0.0f, 0.0f));
	_scale = vec3(1.0f, 1.0f, 1.0f);
	// Se obtiene la matriz identidad si se multiplican las matrices
	// de posición, rotación y escala
	_modelMatrix = mat4(1.0f);

	// Están alineados con los ejes del mundo, los del personaje
	_forward = WORLD_FORWARD_VECTOR;
	_up = WORLD_UP_VECTOR;
	_right = WORLD_RIGHT_VECTOR;
}

mat4 Transform::GetModelMatrix(){
	return _modelMatrix;
}

vec3 Transform::GetPosition(){
	return _position;
}

quat Transform::GetRotation(){
	return _rotation;
}

vec3 Transform::GetScale(){
	return _scale;
}

void Transform::SetPosition(float x, float y, float z){
	_position = vec3(x, y, z);
	// Actualizar la matriz de modelo debido a un cambio de posición
	UpdateModelMatrixPosition();
}

void Transform::SetRotation(float x, float y, float z){
	_rotation = quat(radians(vec3(x, y, z)));
	// La matriz de modelo cambia debido al update de rotación o escala
	UpdateModelMatrixRotationScale();
}

void Transform::SetScale(float x, float y, float z){
	_scale = vec3(x, y, z);
	// Como cambio la escala, hay que actualizar la matriz de modelo
	UpdateModelMatrixRotationScale();
	// La de posición es difenrente porque las posiciones en xyz son diferentes, no se comparten
}

void Transform::Translate(float x, float y, float z, bool world){
	if (world)
		_position += vec3(x, y, z);
	else {
		_position += _forward * z;
		_position += _up * y;
		_position += _right * x;
	}
	UpdateModelMatrixPosition();
}

void Transform::MoveForward(float delta, bool world){
	if (world)
		_position += WORLD_FORWARD_VECTOR*delta;
	else
		_position += _forward * delta;
	UpdateModelMatrixPosition();
}

void Transform::MoveUp(float delta, bool world){
	if (world)
		_position += WORLD_UP_VECTOR*delta;
	else
		_position += _up * delta;
	UpdateModelMatrixPosition();
}

void Transform::MoveRight(float delta, bool world){
	if (world)
		_position += WORLD_RIGHT_VECTOR*delta;
	else
		_position += _right * delta;
	UpdateModelMatrixPosition();
}

void Transform::Rotate(float x, float y, float z, bool world){
	// Representa la rotación que me están pidiendo que tenga
	quat newRotation = quat(radians(vec3(x, y, z)));
	// La multiplicación de los quaterniones no es conmutativa
	if (world)
		_rotation = newRotation * _rotation;
	else 
		_rotation = _rotation * newRotation;
	UpdateModelMatrixRotationScale();
}

void Transform::UpdateLocalVectors(){
	// Solo se calcula una vez que hayas rotado
	mat4 rotationMatrix = mat4_cast(_rotation);
	_forward = vec3(rotationMatrix * vec4(WORLD_FORWARD_VECTOR, 0.0f));
	_up = vec3(rotationMatrix * vec4(WORLD_UP_VECTOR, 0.0f));
	_right = cross(_up, _forward);
}

void Transform::UpdateModelMatrixPosition() {
	// Esta en la última columna, en los primeros tres renglones
	_modelMatrix[3][0] = _position.x;
	_modelMatrix[3][1] = _position.y;
	_modelMatrix[3][2] = _position.z;
}

void Transform::UpdateModelMatrixRotationScale() {
	_modelMatrix = mat4_cast(_rotation);
	_modelMatrix[0] *= _scale.x;
	_modelMatrix[1] *= _scale.y;
	_modelMatrix[2] *= _scale.z;
	UpdateModelMatrixPosition();
	UpdateLocalVectors();
}
