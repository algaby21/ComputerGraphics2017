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
		void SetHeight(double h);
		float GetArea();
		float GetPerimetre();
};