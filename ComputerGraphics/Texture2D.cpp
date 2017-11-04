/*********************************************************
Materia: Gráficas Computacionales
Fecha: 30 de octubre de 2017
Autor: A01169073 Aldo A. Reyna Gómez
*********************************************************/

#include <iostream>
#include "Texture2D.h"
using namespace std;


Texture2D::Texture2D(){
	// Inicializa los valores por default de las variables.
	textureID = 0;
}

Texture2D::~Texture2D(){
	glDeleteTextures(1, &textureID);
}

void Texture2D::LoadTexture(string path){
	// Tipo de dato principal de DevIL
	ILuint imageID;
	ilGenImages(1, &imageID);
	ilBindImage(imageID);
	ilLoadImage(path.c_str());

	// Manejar la imagen como RGBA
	// Serpa un unisgned byte (ligero y fácil de renderear)
	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

	glGenTextures(1, &textureID);
	Bind();

	// Texture filter y texture wrap
	// Para el filtro de minificación
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// Para el filtro de magnificación
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // S coord
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // T coord
	
	glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_FORMAT),
		ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT),
		0, ilGetInteger(IL_IMAGE_FORMAT), ilGetInteger(IL_IMAGE_TYPE),
		ilGetData());

	Unbind();
	ilBindImage(0);
	ilDeleteImages(1, &imageID);
}

void Texture2D::Bind(){
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture2D::Unbind(){
	glBindTexture(GL_TEXTURE_2D, 0);
}
