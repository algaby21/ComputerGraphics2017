/*********************************************************
Materia: Gráficas Computacionales
Fecha: 18 de agosto del 2017
Autor: A01169073 Aldo A. Reyna Gómez
*********************************************************/

#include "Circle.h" //Si es un archivo fuente que ya existe, se usa "", si es librería que se vincula de otro lado, se usa <>

Circle::Circle() { // De la case Circle, voy a implementar el constructor Circle
	_radius = 1.0;
	_colour = "red";
}

Circle::Circle(double r) {
	_radius = r;
	_colour = "verde";
}

Circle::Circle(double r, string c){
	_radius = r;
	_colour = c;
}

double Circle::GetRadius() {
	return _radius;
}

double Circle::GetArea() {
	return 3.14159*_radius*_radius;
}

string Circle::GetColor(){
	return _colour;
}

void Circle::SetRadius(double r){
	_radius = r;
}

void Circle::SetColor(string c){
	_colour = c;
}

