/*********************************************************
Materia: Gráficas Computacionales
Fecha: 18 de agosto del 2017
Autor: A01169073 Aldo A. Reyna Gómez
*********************************************************/

#pragma once
#include <string>

using namespace std;

class Rectangle {
	private:
		float _width;
		float _height;

	public:
		Rectangle();
		Rectangle(float w, float h);
		float GetWidth();
		void SetWidth(float w);
		float GetHeight();
		void SetHeight(float h);
		float GetArea();
		float GetPerimetre();
};