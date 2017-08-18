/*********************************************************
Materia: Gráficas Computacionales
Fecha: 18 de agosto del 2017
Autor: A01169073 Aldo A. Reyna Gómez
*********************************************************/

#include "Rectangle.h"

Rectangle::Rectangle() {
	_width = 1.0f;
	_height = 1.0f;
}

Rectangle::Rectangle(float w, float h){
	_width = w;
	_height = h;
}

float Rectangle::GetWidth(){
	return _width;
}

void Rectangle::SetWidth(float w){
	_width = w;
}

float Rectangle::GetHeight(){
	return _height;
}

void Rectangle::SetHeight(float h){
	_height = h;
}

float Rectangle::GetArea(){
	return _height*_width;
}

float Rectangle::GetPerimetre(){
	return 2 * _height + 2 * _width;
}
