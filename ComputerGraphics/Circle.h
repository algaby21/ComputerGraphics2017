/*********************************************************
Materia: Gráficas Computacionales
Fecha: 18 de agosto del 2017
Autor: A01169073 Aldo A. Reyna Gómez
*********************************************************/

#pragma once
#include <string>

using namespace std;

class Circle {
	public: 
		Circle(); //Solo los constructores no tienen tipo de regreso
		Circle(double r);
		Circle(double r, string c);

		double GetRadius();
		double GetArea();
		string GetColor();

		void SetRadius(double r);
		void SetColor(string c);

	private:
		double _radius;
		string _colour;
};