/*********************************************************
Materia: Gráficas Computacionales
Fecha: 18 de agosto del 2017
Autor: A01169073 Aldo A. Reyna Gómez
*********************************************************/

#include "InputFile.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

bool InputFile::Read(string filename){
	// Leer un nuevo archivo con el nombre filename
	ifstream file(filename);
	//file.open(filename); // es igual que ifstream file(filename);
	if (file) {
		stringstream buff;
		buff << file.rdbuf();
		file.close();
		_contents = buff.str();
		return true;
	}
	return false;	
}

string InputFile::GetContents(){
	return _contents;
}

/*
 * Bento, M. (2008, septiembre 25). How to read file content into istringstream ? 
 		Retrieved from Stack Overflow : https://stackoverflow.com/questions/132358/how-to-read-file-content-into-istringstream
 * Tutorials Point. (2017, julio 23). C++ Files and Streams.Retrieved from 
 		https://www.tutorialspoint.com/cplusplus/cpp_files_streams.htm
 */


