/*********************************************************
Materia: Gráficas Computacionales
Fecha: 18 de agosto del 2017
Autor: A01169073 Aldo A. Reyna Gómez
*********************************************************/

#pragma once
#include <string>

using namespace std;

class InputFile {
	private:
		string _contents;
	public:
		bool Read(string filename);
		string GetContents();
};