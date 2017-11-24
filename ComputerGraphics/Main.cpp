/*********************************************************
Materia: Gráficas Computacionales
Fecha: 16 de septiembre del 2017
Autor: A01169073 Aldo A. Reyna Gómez
*********************************************************/

#include <IL/il.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <glm/glm.hpp>
#include "glm/gtx/string_cast.hpp"
#include <vector>

#include "Mesh.h"
#include "ShaderProgram.h"	
#include "Transform.h"
#include "Camera.h"
#include "Texture2D.h"
#include "Depthbuffer.h"

using namespace std;
using namespace glm;

// Identificador del manager al que vamos a asociar todos los VBOs que tenga nuestra geometría
unique_ptr<Mesh> meshPalma(new Mesh);
unique_ptr<Mesh> meshFingers(new Mesh);
// Identificador del manager de los shaders (shaderProgram)
// El que tiene una sombra
unique_ptr<ShaderProgram> shaderProgram1(new ShaderProgram);
// El que tiene dos sombras
unique_ptr<ShaderProgram> shaderProgram2(new ShaderProgram);
// El que no sirve para nada
unique_ptr<ShaderProgram> shaderProgram3(new ShaderProgram);

unique_ptr<Transform> geometria1(new Transform); // Geometría 1: cubo rotando
unique_ptr<Transform> geometria2(new Transform); // Geometría 2: cubo piso estático
unique_ptr<Transform> geometria3(new Transform); 
unique_ptr<Transform> geometria4(new Transform);
unique_ptr<Transform> geometria5(new Transform);
unique_ptr<Transform> geometria6(new Transform);
unique_ptr<Transform> geometria7(new Transform);
unique_ptr<Transform> geometria8(new Transform);
unique_ptr<Transform> geometria9(new Transform);
unique_ptr<Transform> geometria10(new Transform);

unique_ptr<Camera> camara1(new Camera); // Cámara donde se encuentra el observador
unique_ptr<Camera> camara2(new Camera); // Cámara donde se ubica la fuente de luz

Texture2D myTexture1;
Texture2D myTexture2;
Texture2D myTexture3;
//unique_ptr<Texture2D> myTexture3(new Texture2D);

unique_ptr<Depthbuffer> myFramebuffer(new Depthbuffer);

// Identificador del manager al que vamos a asociar todos los VBOs que tenga nuestra geometría
GLuint vao;

// Identificador del manager de los shaders (shaderProgramme)
// GLuint shaderProgram;

float pos = 0.0; // Índice para la trayectoria del círculo de la geometría1
float deltaCirculo = 0.01f;
float inc = 0.0;
float inc2 = 0.0;
float inc3 = 0.0;
float deltaMovimiento = 0.00f;
float deltaMovimiento2 = 0.00f;
float deltaMovimiento3 = 0.00f;
double colour = 0.0; // Color de fondo
vec3 lightColour = vec3(1.0f, 1.0f, 1.0f);
vec3 lightPosition = vec3(-5.0f, 5.0f, 5.0f);

void ReshapeWindow(int width, int height) {
	// Para configurar un uniform, tenemos que decirle a OpenGL que vamos a utilizar el shader program (manager)
	glViewport(0, 0, width, height);
	//shProgram.SetUniform("Resolution", width, height);
}


void Initialise() {
	vector<vec3> positions1;
	vector<vec3> colors1;
	vector<vec3> normals1;
	vector<vec2> textures1;

	/*float arr[6] = { 18.f, 306.f, 234.f, 162.f, 90.f, 18.f };
	for (int i = 0; i < 6; i++) {
	positions.push_back(vec2(cos(radians(arr[i])), sin(radians(arr[i]))));
	colors.push_back(vec3(0.0f, 0.0f, 1.0f));
	positions.push_back(vec2(0.5*cos(radians(arr[i])), 0.5*sin(radians(arr[i]))));
	colors.push_back(vec3(1.0f, 0.0f, 0.0f));
	}*/

	float scaleX = 1.5f;
	float scaleY = 1.5f;
	float scaleZ = 0.1f;

	// Cara frontal
	positions1.push_back(vec3(-3.0f*scaleX, -3.0f*scaleY, 3.0f*scaleZ));
	positions1.push_back(vec3(3.0f*scaleX, -3.0f*scaleY, 3.0f*scaleZ));
	positions1.push_back(vec3(3.0f*scaleX, 3.0f*scaleY, 3.0f*scaleZ));
	positions1.push_back(vec3(-3.0f*scaleX, 3.0f*scaleY, 3.0f*scaleZ));
	normals1.push_back(vec3(0.0f, 0.0f, 1.0f));
	normals1.push_back(vec3(0.0f, 0.0f, 1.0f));
	normals1.push_back(vec3(0.0f, 0.0f, 1.0f));
	normals1.push_back(vec3(0.0f, 0.0f, 1.0f));
	textures1.push_back(vec2(0.0f, 0.0f));
	textures1.push_back(vec2(1.0f, 0.0f));
	textures1.push_back(vec2(1.0f, 1.0f));
	textures1.push_back(vec2(0.0f, 1.0f));

	// Cara lateral derecha
	positions1.push_back(vec3(3.0f*scaleX, 3.0f*scaleY, 3.0f*scaleZ));
	positions1.push_back(vec3(3.0f*scaleX, 3.0f*scaleY, -3.0f*scaleZ));
	positions1.push_back(vec3(3.0f*scaleX, -3.0f*scaleY, -3.0f*scaleZ));
	positions1.push_back(vec3(3.0f*scaleX, -3.0f*scaleY, 3.0f*scaleZ));
	normals1.push_back(vec3(1.0f, 0.0f, 0.0f));
	normals1.push_back(vec3(1.0f, 0.0f, 0.0f));
	normals1.push_back(vec3(1.0f, 0.0f, 0.0f));
	normals1.push_back(vec3(1.0f, 0.0f, 0.0f));
	textures1.push_back(vec2(0.0f, 0.0f));
	textures1.push_back(vec2(1.0f, 0.0f));
	textures1.push_back(vec2(1.0f, 1.0f));
	textures1.push_back(vec2(0.0f, 1.0f));

	// Cara trasera
	positions1.push_back(vec3(-3.0f*scaleX, -3.0f*scaleY, -3.0f*scaleZ));
	positions1.push_back(vec3(3.0f*scaleX, -3.0f*scaleY, -3.0f*scaleZ));
	positions1.push_back(vec3(3.0f*scaleX, 3.0f*scaleY, -3.0f*scaleZ));
	positions1.push_back(vec3(-3.0f*scaleX, 3.0f*scaleY, -3.0f*scaleZ));
	normals1.push_back(vec3(0.0f, 0.0f, -1.0f));
	normals1.push_back(vec3(0.0f, 0.0f, -1.0f));
	normals1.push_back(vec3(0.0f, 0.0f, -1.0f));
	normals1.push_back(vec3(0.0f, 0.0f, -1.0f));
	textures1.push_back(vec2(0.0f, 0.0f));
	textures1.push_back(vec2(1.0f, 0.0f));
	textures1.push_back(vec2(1.0f, 1.0f));
	textures1.push_back(vec2(0.0f, 1.0f));

	// Cara lateral izquierda
	positions1.push_back(vec3(-3.0f*scaleX, -3.0f*scaleY, -3.0f*scaleZ));
	positions1.push_back(vec3(-3.0f*scaleX, -3.0f*scaleY, 3.0f*scaleZ));
	positions1.push_back(vec3(-3.0f*scaleX, 3.0f*scaleY, 3.0f*scaleZ));
	positions1.push_back(vec3(-3.0f*scaleX, 3.0f*scaleY, -3.0f*scaleZ));
	normals1.push_back(vec3(-1.0f, 0.0f, 0.0f));
	normals1.push_back(vec3(-1.0f, 0.0f, 0.0f));
	normals1.push_back(vec3(-1.0f, 0.0f, 0.0f));
	normals1.push_back(vec3(-1.0f, 0.0f, 0.0f));
	textures1.push_back(vec2(0.0f, 0.0f));
	textures1.push_back(vec2(1.0f, 0.0f));
	textures1.push_back(vec2(1.0f, 1.0f));
	textures1.push_back(vec2(0.0f, 1.0f));

	// Cara superior
	positions1.push_back(vec3(3.0f*scaleX, 3.0f*scaleY, 3.0f*scaleZ));
	positions1.push_back(vec3(-3.0f*scaleX, 3.0f*scaleY, 3.0f*scaleZ));
	positions1.push_back(vec3(-3.0f*scaleX, 3.0f*scaleY, -3.0f*scaleZ));
	positions1.push_back(vec3(3.0f*scaleX, 3.0f*scaleY, -3.0f*scaleZ));
	normals1.push_back(vec3(0.0f, 1.0f, 0.0f));
	normals1.push_back(vec3(0.0f, 1.0f, 0.0f));
	normals1.push_back(vec3(0.0f, 1.0f, 0.0f));
	normals1.push_back(vec3(0.0f, 1.0f, 0.0f));
	textures1.push_back(vec2(0.0f, 0.0f));
	textures1.push_back(vec2(1.0f, 0.0f));
	textures1.push_back(vec2(1.0f, 1.0f));
	textures1.push_back(vec2(0.0f, 1.0f));

	// Cara inferior
	positions1.push_back(vec3(-3.0f*scaleX, -3.0f*scaleY, -3.0f*scaleZ));
	positions1.push_back(vec3(3.0f*scaleX, -3.0f*scaleY, -3.0f*scaleZ));
	positions1.push_back(vec3(3.0f*scaleX, -3.0f*scaleY, 3.0f*scaleZ));
	positions1.push_back(vec3(-3.0f*scaleX, -3.0f*scaleY, 3.0f*scaleZ));
	normals1.push_back(vec3(0.0f, -1.0f, 0.0f));
	normals1.push_back(vec3(0.0f, -1.0f, 0.0f));
	normals1.push_back(vec3(0.0f, -1.0f, 0.0f));
	normals1.push_back(vec3(0.0f, -1.0f, 0.0f));
	textures1.push_back(vec2(0.0f, 0.0f));
	textures1.push_back(vec2(1.0f, 0.0f));
	textures1.push_back(vec2(1.0f, 1.0f));
	textures1.push_back(vec2(0.0f, 1.0f));

	vector<unsigned int> indices = {
		0, 1, 2, 0, 2, 3, // Frontal
		4, 5, 6, 4, 6, 7, // Derecha
		8, 9, 10, 8, 10, 11, // Trasera
		12, 13, 14, 12, 14, 15, // Izquierda
		16, 17, 18, 16, 18, 19, // Superior
		20, 21, 22, 20, 22, 23 // Inferior
	};

	meshPalma->CreateMesh(positions1.size());
	meshPalma->SetPositionAttribute(positions1, GL_STATIC_DRAW, 0);
	meshPalma->SetColorAttribute(colors1, GL_STATIC_DRAW, 1);
	meshPalma->SetNormalAttribute(normals1, GL_STATIC_DRAW, 2);
	meshPalma->SetTexCoordAttribute(textures1, GL_STATIC_DRAW, 3);
	meshPalma->SetIndices(indices, GL_STATIC_DRAW);


	vector<vec3> positions2;
	vector<vec3> colors2;
	vector<vec3> normals2;
	vector<vec2> textures2;

	/*float arr[6] = { 18.f, 306.f, 234.f, 162.f, 90.f, 18.f };
	for (int i = 0; i < 6; i++) {
	positions.push_back(vec2(cos(radians(arr[i])), sin(radians(arr[i]))));
	colors.push_back(vec3(0.0f, 0.0f, 1.0f));
	positions.push_back(vec2(0.5*cos(radians(arr[i])), 0.5*sin(radians(arr[i]))));
	colors.push_back(vec3(1.0f, 0.0f, 0.0f));
	}*/

	scaleX = 0.4f;
	scaleY = 0.7f;
	scaleZ = 0.1f;

	// Cara frontal
	positions2.push_back(vec3(-3.0f*scaleX, -3.0f*scaleY, 3.0f*scaleZ));
	positions2.push_back(vec3(3.0f*scaleX, -3.0f*scaleY, 3.0f*scaleZ));
	positions2.push_back(vec3(3.0f*scaleX, 3.0f*scaleY, 3.0f*scaleZ));
	positions2.push_back(vec3(-3.0f*scaleX, 3.0f*scaleY, 3.0f*scaleZ));
	normals2.push_back(vec3(0.0f, 0.0f, 1.0f));
	normals2.push_back(vec3(0.0f, 0.0f, 1.0f));
	normals2.push_back(vec3(0.0f, 0.0f, 1.0f));
	normals2.push_back(vec3(0.0f, 0.0f, 1.0f));
	textures2.push_back(vec2(0.0f, 0.0f));
	textures2.push_back(vec2(1.0f, 0.0f));
	textures2.push_back(vec2(1.0f, 1.0f));
	textures2.push_back(vec2(0.0f, 1.0f));

	// Cara lateral derecha
	positions2.push_back(vec3(3.0f*scaleX, 3.0f*scaleY, 3.0f*scaleZ));
	positions2.push_back(vec3(3.0f*scaleX, 3.0f*scaleY, -3.0f*scaleZ));
	positions2.push_back(vec3(3.0f*scaleX, -3.0f*scaleY, -3.0f*scaleZ));
	positions2.push_back(vec3(3.0f*scaleX, -3.0f*scaleY, 3.0f*scaleZ));
	normals2.push_back(vec3(1.0f, 0.0f, 0.0f));
	normals2.push_back(vec3(1.0f, 0.0f, 0.0f));
	normals2.push_back(vec3(1.0f, 0.0f, 0.0f));
	normals2.push_back(vec3(1.0f, 0.0f, 0.0f));
	textures2.push_back(vec2(0.0f, 0.0f));
	textures2.push_back(vec2(1.0f, 0.0f));
	textures2.push_back(vec2(1.0f, 1.0f));
	textures2.push_back(vec2(0.0f, 1.0f));

	// Cara trasera
	positions2.push_back(vec3(-3.0f*scaleX, -3.0f*scaleY, -3.0f*scaleZ));
	positions2.push_back(vec3(3.0f*scaleX, -3.0f*scaleY, -3.0f*scaleZ));
	positions2.push_back(vec3(3.0f*scaleX, 3.0f*scaleY, -3.0f*scaleZ));
	positions2.push_back(vec3(-3.0f*scaleX, 3.0f*scaleY, -3.0f*scaleZ));
	normals2.push_back(vec3(0.0f, 0.0f, -1.0f));
	normals2.push_back(vec3(0.0f, 0.0f, -1.0f));
	normals2.push_back(vec3(0.0f, 0.0f, -1.0f));
	normals2.push_back(vec3(0.0f, 0.0f, -1.0f));
	textures2.push_back(vec2(0.0f, 0.0f));
	textures2.push_back(vec2(1.0f, 0.0f));
	textures2.push_back(vec2(1.0f, 1.0f));
	textures2.push_back(vec2(0.0f, 1.0f));

	// Cara lateral izquierda
	positions2.push_back(vec3(-3.0f*scaleX, -3.0f*scaleY, -3.0f*scaleZ));
	positions2.push_back(vec3(-3.0f*scaleX, -3.0f*scaleY, 3.0f*scaleZ));
	positions2.push_back(vec3(-3.0f*scaleX, 3.0f*scaleY, 3.0f*scaleZ));
	positions2.push_back(vec3(-3.0f*scaleX, 3.0f*scaleY, -3.0f*scaleZ));
	normals2.push_back(vec3(-1.0f, 0.0f, 0.0f));
	normals2.push_back(vec3(-1.0f, 0.0f, 0.0f));
	normals2.push_back(vec3(-1.0f, 0.0f, 0.0f));
	normals2.push_back(vec3(-1.0f, 0.0f, 0.0f));
	textures2.push_back(vec2(0.0f, 0.0f));
	textures2.push_back(vec2(1.0f, 0.0f));
	textures2.push_back(vec2(1.0f, 1.0f));
	textures2.push_back(vec2(0.0f, 1.0f));

	// Cara superior
	positions2.push_back(vec3(3.0f*scaleX, 3.0f*scaleY, 3.0f*scaleZ));
	positions2.push_back(vec3(-3.0f*scaleX, 3.0f*scaleY, 3.0f*scaleZ));
	positions2.push_back(vec3(-3.0f*scaleX, 3.0f*scaleY, -3.0f*scaleZ));
	positions2.push_back(vec3(3.0f*scaleX, 3.0f*scaleY, -3.0f*scaleZ));
	normals2.push_back(vec3(0.0f, 1.0f, 0.0f));
	normals2.push_back(vec3(0.0f, 1.0f, 0.0f));
	normals2.push_back(vec3(0.0f, 1.0f, 0.0f));
	normals2.push_back(vec3(0.0f, 1.0f, 0.0f));
	textures2.push_back(vec2(0.0f, 0.0f));
	textures2.push_back(vec2(1.0f, 0.0f));
	textures2.push_back(vec2(1.0f, 1.0f));
	textures2.push_back(vec2(0.0f, 1.0f));

	// Cara inferior
	positions2.push_back(vec3(-3.0f*scaleX, -3.0f*scaleY, -3.0f*scaleZ));
	positions2.push_back(vec3(3.0f*scaleX, -3.0f*scaleY, -3.0f*scaleZ));
	positions2.push_back(vec3(3.0f*scaleX, -3.0f*scaleY, 3.0f*scaleZ));
	positions2.push_back(vec3(-3.0f*scaleX, -3.0f*scaleY, 3.0f*scaleZ));
	normals2.push_back(vec3(0.0f, -1.0f, 0.0f));
	normals2.push_back(vec3(0.0f, -1.0f, 0.0f));
	normals2.push_back(vec3(0.0f, -1.0f, 0.0f));
	normals2.push_back(vec3(0.0f, -1.0f, 0.0f));
	textures2.push_back(vec2(0.0f, 0.0f));
	textures2.push_back(vec2(1.0f, 0.0f));
	textures2.push_back(vec2(1.0f, 1.0f));
	textures2.push_back(vec2(0.0f, 1.0f));


	meshFingers->CreateMesh(positions2.size());
	meshFingers->SetPositionAttribute(positions2, GL_STATIC_DRAW, 0);
	meshFingers->SetColorAttribute(colors2, GL_STATIC_DRAW, 1);
	meshFingers->SetNormalAttribute(normals2, GL_STATIC_DRAW, 2);
	meshFingers->SetTexCoordAttribute(textures2, GL_STATIC_DRAW, 3);
	meshFingers->SetIndices(indices, GL_STATIC_DRAW);

	/*
	// Queremos gengerar 1 manager
	glGenVertexArrays(1, &vao);
	// Utilizar el vao
	// A partir de este momento, todos los VBOs creados y configurados se van a asociar a este manager
	glBindVertexArray(vao);

	// Tipo de dato de OpenGL entero sin signo multiplataforma
	// Empezamos a crear bufers (identificador de VBO de posiciones)
	GLuint positionsVBO;
	// Creación del VBO de posiciones lo guarda en positionsVBO y da un identificador para utilizarlo
	glGenBuffers(1, &positionsVBO);
	// Activamos el buffer de posiciones para poder utilizarlo, este buffer ES UN ATRIBUTO (GL ARRAY BUFFER)
	glBindBuffer(GL_ARRAY_BUFFER, positionsVBO);
	// Creamos la memoria y la inicializamos con los datos del atributo de posiciones
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec2)*positions.size(), positions.data(), GL_STATIC_DRAW);
	// Activamos el atributo en la tarjeta de video
	glEnableVertexAttribArray(0);
	// Configuramos los datos del atributo en la tarjeta de video
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	// Ya no vamos a utilizar este Vertex Buffer Object en este momento
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GLuint colorsVBO;
	glGenBuffers(1, &colorsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3)*colors.size(), colors.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, 0);*/

	/*
	// Creamos un objeto para leer archivos
	InputFile myfile;

	// VERTEX SHADER
	// Leemos el archivo Default.vert donde está el código del vertex shader.
	myfile.Read("Default.vert");
	// Obtenemos el código fuente y lo guardamos en un string
	string vertexSource = myfile.GetContents();
	// Creamos un shader de tipo vertex guardamos su identificador en una variable
	GLuint vertexShaderHandle =
	glCreateShader(GL_VERTEX_SHADER);
	// Obtener los datos en el formato correcto: Vil Cast
	const GLchar *vertexSource_c =
	(const GLchar*)vertexSource.c_str();
	// Le estamos dando el código fuente a OpenGL para que se los asigne al shader
	glShaderSource(vertexShaderHandle, 1, &vertexSource_c, nullptr);
	// Compilamos el shader en busca de errores.
	// Vamos a asumir que no hay ningún error.
	glCompileShader(vertexShaderHandle);

	myfile.Read("Default.frag");
	string fragmentSource = myfile.GetContents();
	GLuint fragmentShaderHandle =
	glCreateShader(GL_FRAGMENT_SHADER);
	const GLchar *fragmentSource_c =
	(const GLchar*)fragmentSource.c_str();
	// Continuar leyendo hasta que encuentre un nullptr
	glShaderSource(fragmentShaderHandle, 1, &fragmentSource_c, nullptr);
	glCompileShader(fragmentShaderHandle);*/

	// Creando-cargando las texturas que se dibujarán
	myTexture1.LoadTexture("box.jpg");
	myTexture2.LoadTexture("pig.jpg");
	myTexture3.LoadTexture("tiled.jpg");


	// Hacer la cámara hacia el observador para una mejor vista
	camara1->MoveForward(30.0f);
	camara1->MoveUp(12.0);
	camara1->Pitch(-30);

	// Creación y activación del primer shader program (Solo 1 sombra)
	shaderProgram1->CreateProgram();
	shaderProgram1->AttachShader("Shadow.vert", GL_VERTEX_SHADER);
	shaderProgram1->AttachShader("Shadow.frag", GL_FRAGMENT_SHADER);
	shaderProgram1->SetAttribute(0, "VertexPosition");
	shaderProgram1->SetAttribute(1, "VertexColour");
	shaderProgram1->SetAttribute(2, "VertexNormal");
	shaderProgram1->SetAttribute(3, "VertexTexCoord");
	shaderProgram1->LinkProgram();
	shaderProgram1->Activate();
	// Aquí se envía la luz como uniform al fragment shader
	shaderProgram1->SetUniform("LightPosition", lightPosition.x, lightPosition.y, lightPosition.z);
	shaderProgram1->SetUniform("LightColour", lightColour.x, lightColour.y, lightColour.z);
	shaderProgram1->SetUniform("CameraPosition", camara1->GetPosition().x, camara1->GetPosition().y, camara1->GetPosition().z);
	// Se envía como uniform el nombre de la textura junto con el índice
	// Se tienen máximo 2 texturas dibujando en un mismo objeto
	// por lo que solo habrán dos índices
	shaderProgram1->SetUniformi("DiffuseTexture", 0);
	shaderProgram1->SetUniformi("DiffuseTexture1", 1);
	shaderProgram1->SetUniformi("ShadowMap", 2);
	shaderProgram1->Deactivate();

	// Creación y activación del segundo shader program (2 sombras)
	shaderProgram2->CreateProgram();
	shaderProgram2->AttachShader("Shadow2.vert", GL_VERTEX_SHADER);
	shaderProgram2->AttachShader("Shadow2.frag", GL_FRAGMENT_SHADER);
	shaderProgram2->SetAttribute(0, "VertexPosition");
	shaderProgram2->SetAttribute(1, "VertexColour");
	shaderProgram2->SetAttribute(2, "VertexNormal");
	shaderProgram2->SetAttribute(3, "VertexTexCoord");
	shaderProgram2->LinkProgram();
	shaderProgram2->Activate();
	shaderProgram2->SetUniform("LightPosition", lightPosition.x, lightPosition.y, lightPosition.z);
	shaderProgram2->SetUniform("LightColour", lightColour.x, lightColour.y, lightColour.z);
	shaderProgram2->SetUniform("CameraPosition", camara1->GetPosition().x, camara1->GetPosition().y, camara1->GetPosition().z);
	shaderProgram2->SetUniformi("DiffuseTexture", 0);
	shaderProgram2->SetUniformi("DiffuseTexture1", 1);
	shaderProgram2->SetUniformi("ShadowMap", 2);
	shaderProgram2->Deactivate();

	// Creación y activación del tercer shader program (el que no sirve para nada)
	shaderProgram3->CreateProgram();
	shaderProgram3->AttachShader("Depth.vert", GL_VERTEX_SHADER);
	shaderProgram3->AttachShader("Depth.frag", GL_FRAGMENT_SHADER);
	shaderProgram3->SetAttribute(0, "VertexPosition");
	shaderProgram3->LinkProgram();


	// --------------- Creación y configuración del framebuffer con 2048 px ------------------
	myFramebuffer->Create(2048);

	// --------------- Configuración de las cámaras ------------------


	// Se acomoda la segunda cámara en la posición de la luz y debe ser ortográfica
	// para que los rayos sean infinitamente lejos y con el mismo ángulo (?)
	camara2->SetPosition(lightPosition.x, lightPosition.y, lightPosition.z);
	camara2->SetOrthographic(30.0, 1.0);
	camara2->Pitch(-45);

	// Escala y rotación de la palma
	//geometria1->SetScale(1.5f, 1.5f, 0.2f);
	geometria1->Rotate(-60.0f, 0.0f, 0.0f, false);
	
	// Acomodo de la geometría2 (piso) ¡NO QUEDA! D:
	geometria2->SetScale(6.0f, 0.2f, 40.0f);
	geometria2->MoveUp(-14.0f, true);
	geometria2->MoveForward(-10.0f, true);
	geometria2->Rotate(20, 0, 0, true);

	geometria3->MoveRight(-3.0f, true);
	geometria3->MoveUp(7.0f, true);

	geometria4->MoveRight(0.0f, true);
	geometria4->MoveUp(7.0f, true);

	geometria5->MoveRight(3.0f, true);
	geometria5->MoveUp(7.0f, true);

	geometria6->MoveRight(7.0f, true);
	geometria6->MoveUp(-1.0f, true);
	geometria6->Rotate(0, 0, -85, false);

	geometria7->MoveUp(4.5f, true);

	geometria8->MoveUp(4.5f, true);

	geometria9->MoveUp(4.5f, true);

	geometria10->MoveUp(4.5f, true);

	/*
	// Regresa el identificador de este manager
	// Creamos el identificador para el manager de los shaders
	shaderProgram = glCreateProgram();
	// Adjuntamos el vertex shader del manager (van a trabajar juntos)
	glAttachShader(shaderProgram, vertexShaderHandle);
	// Adjuntamos el fragment shader al manager (van a trabajar juntos)
	glAttachShader(shaderProgram, fragmentShaderHandle);
	// Asociamos un buffer con índice 0 (posiciones) a la variable VertexPosition
	glBindAttribLocation(shaderProgram, 0, "VertexPosition");
	// Asociamos un buffer con índice 1 (colores) a la variable VertexColor
	glBindAttribLocation(shaderProgram, 1, "VertexColor");
	// Ejecutamos el proceso de linker (asegurarnos que el vertex y fragment son compatibles)
	glLinkProgram(shaderProgram);*/
}

void GameLoop() {
	// Siempre hacerlo al inicio del frame!
	geometria1->Rotate(0.0f, 0.01f, 0.01f, false);

	if (inc >= 90.0f || inc < 0.0f) {
		deltaMovimiento *= -1.0f;
	}
	inc += deltaMovimiento;

	if (inc2 >= 90.0f || inc2 < 0.0f) {
		deltaMovimiento2 *= -1.0f;
	}
	inc2 += deltaMovimiento2;

	if (inc3 >= 90.0f || inc3 < 0.0f) {
		deltaMovimiento3 *= -1.0f;
	}
	inc3 += deltaMovimiento3;

	geometria3->Rotate(deltaMovimiento, 0, 0, false);
	geometria3->MoveForward(deltaMovimiento / 30 + sin(radians(deltaMovimiento)) , false);

	geometria4->Rotate(deltaMovimiento2, 0, 0, false);
	geometria4->MoveForward(deltaMovimiento2 / 30 + sin(radians(deltaMovimiento2)), false);

	geometria5->Rotate(deltaMovimiento3, 0, 0, false);
	geometria5->MoveForward(deltaMovimiento3 / 30 + sin(radians(deltaMovimiento3)), false);

	geometria6->Rotate(deltaMovimiento3, 0, 0, false);
	geometria6->MoveForward(deltaMovimiento3 / 30 + sin(radians(deltaMovimiento3)), false);

	geometria7->Rotate(deltaMovimiento, 0, 0, false);
	geometria7->MoveForward(deltaMovimiento / 30 + sin(radians(deltaMovimiento)), false);

	geometria8->Rotate(deltaMovimiento2, 0, 0, false);
	geometria8->MoveForward(deltaMovimiento2 / 30 + sin(radians(deltaMovimiento2)), false);

	geometria9->Rotate(deltaMovimiento3, 0, 0, false);
	geometria9->MoveForward(deltaMovimiento3 / 30 + sin(radians(deltaMovimiento3)), false);

	geometria10->Rotate(deltaMovimiento3, 0, 0, false);
	geometria10->MoveForward(deltaMovimiento3 / 30 + sin(radians(deltaMovimiento3)), false);
	

	deltaMovimiento += 0.000008f;
	deltaMovimiento2 += 0.000009f;
	deltaMovimiento3 += 0.00001f;

	
	// ---------------------------------- 1er Render ----------------------------------

	myFramebuffer->Bind();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shaderProgram3->Activate();

	// Geometría 1
	shaderProgram3->SetUniformMatrix("mvpMatrix", camara2->GetViewProjection()*geometria1->GetModelMatrix());
	meshPalma->Draw(GL_TRIANGLES);

	// Geometría 2
	shaderProgram3->SetUniformMatrix("mvpMatrix", camara2->GetViewProjection()*geometria2->GetModelMatrix());
	meshPalma->Draw(GL_TRIANGLES);

	// Geometría 3
	shaderProgram3->SetUniformMatrix("mvpMatrix", camara2->GetViewProjection()*geometria1->GetModelMatrix()*geometria3->GetModelMatrix());
	meshFingers->Draw(GL_TRIANGLES);

	// Geometría 4
	shaderProgram3->SetUniformMatrix("mvpMatrix", camara2->GetViewProjection()*geometria1->GetModelMatrix()*geometria4->GetModelMatrix());
	meshFingers->Draw(GL_TRIANGLES);

	// Geometría 5
	shaderProgram3->SetUniformMatrix("mvpMatrix", camara2->GetViewProjection()*geometria1->GetModelMatrix()*geometria5->GetModelMatrix());
	meshFingers->Draw(GL_TRIANGLES);

	// Geometría 6
	shaderProgram3->SetUniformMatrix("mvpMatrix", camara2->GetViewProjection()*geometria1->GetModelMatrix()*geometria6->GetModelMatrix());
	meshFingers->Draw(GL_TRIANGLES);

	// Geometría 7
	shaderProgram3->SetUniformMatrix("mvpMatrix", camara2->GetViewProjection()*geometria1->GetModelMatrix()*geometria3->GetModelMatrix()*geometria7->GetModelMatrix());
	meshFingers->Draw(GL_TRIANGLES);
	
	// Geometría 8
	shaderProgram3->SetUniformMatrix("mvpMatrix", camara2->GetViewProjection()*geometria1->GetModelMatrix()*geometria3->GetModelMatrix()*geometria8->GetModelMatrix());
	meshFingers->Draw(GL_TRIANGLES);

	// Geometría 9
	shaderProgram3->SetUniformMatrix("mvpMatrix", camara2->GetViewProjection()*geometria1->GetModelMatrix()*geometria3->GetModelMatrix()*geometria9->GetModelMatrix());
	meshFingers->Draw(GL_TRIANGLES);

	// Geometría 10
	shaderProgram3->SetUniformMatrix("mvpMatrix", camara2->GetViewProjection()*geometria1->GetModelMatrix()*geometria6->GetModelMatrix()*geometria10->GetModelMatrix());
	meshFingers->Draw(GL_TRIANGLES);

	shaderProgram3->Deactivate();

	myFramebuffer->Unbind();
	ReshapeWindow(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));

	// ---------------------------------- 2do Render ----------------------------------
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	shaderProgram2->Activate();
	// Geometría 1
	glActiveTexture(GL_TEXTURE0);
	myTexture1.Bind();
	glActiveTexture(GL_TEXTURE1);
	myTexture2.Bind();
	glActiveTexture(GL_TEXTURE2);
	myFramebuffer->BindDepthMap();

	mat4 modelMatrix = geometria1->GetModelMatrix();
	mat3 normalMatrix = transpose(inverse(mat3(geometria1->GetModelMatrix())));
	shaderProgram2->SetUniformMatrix("mvpMatrix", camara1->GetViewProjection()*geometria1->GetModelMatrix());
	shaderProgram2->SetUniformMatrix("ModelMatrix", modelMatrix);
	shaderProgram2->SetUniformMatrix("NormalMatrix", normalMatrix);
	shaderProgram2->SetUniformMatrix("LightVPMatrix", camara2->GetViewProjection());
	meshPalma->Draw(GL_TRIANGLES);

	modelMatrix = geometria1->GetModelMatrix()*geometria3->GetModelMatrix();
	normalMatrix = transpose(inverse(mat3(geometria1->GetModelMatrix()*geometria3->GetModelMatrix())));
	shaderProgram2->SetUniformMatrix("mvpMatrix", camara1->GetViewProjection()*geometria1->GetModelMatrix()*geometria3->GetModelMatrix());
	shaderProgram2->SetUniformMatrix("ModelMatrix", modelMatrix);
	shaderProgram2->SetUniformMatrix("NormalMatrix", normalMatrix);
	shaderProgram2->SetUniformMatrix("LightVPMatrix", camara2->GetViewProjection());
	meshFingers->Draw(GL_TRIANGLES);

	modelMatrix = geometria1->GetModelMatrix()*geometria4->GetModelMatrix();
	normalMatrix = transpose(inverse(mat3(geometria1->GetModelMatrix()*geometria4->GetModelMatrix())));
	shaderProgram2->SetUniformMatrix("mvpMatrix", camara1->GetViewProjection()*geometria1->GetModelMatrix()*geometria4->GetModelMatrix());
	shaderProgram2->SetUniformMatrix("ModelMatrix", modelMatrix);
	shaderProgram2->SetUniformMatrix("NormalMatrix", normalMatrix);
	shaderProgram2->SetUniformMatrix("LightVPMatrix", camara2->GetViewProjection());
	meshFingers->Draw(GL_TRIANGLES);

	modelMatrix = geometria1->GetModelMatrix()*geometria5->GetModelMatrix();
	normalMatrix = transpose(inverse(mat3(geometria1->GetModelMatrix()*geometria5->GetModelMatrix())));
	shaderProgram2->SetUniformMatrix("mvpMatrix", camara1->GetViewProjection()*geometria1->GetModelMatrix()*geometria5->GetModelMatrix());
	shaderProgram2->SetUniformMatrix("ModelMatrix", modelMatrix);
	shaderProgram2->SetUniformMatrix("NormalMatrix", normalMatrix);
	shaderProgram2->SetUniformMatrix("LightVPMatrix", camara2->GetViewProjection());
	meshFingers->Draw(GL_TRIANGLES);

	modelMatrix = geometria1->GetModelMatrix()*geometria6->GetModelMatrix();
	normalMatrix = transpose(inverse(mat3(geometria1->GetModelMatrix()*geometria6->GetModelMatrix())));
	shaderProgram2->SetUniformMatrix("mvpMatrix", camara1->GetViewProjection()*geometria1->GetModelMatrix()*geometria6->GetModelMatrix());
	shaderProgram2->SetUniformMatrix("ModelMatrix", modelMatrix);
	shaderProgram2->SetUniformMatrix("NormalMatrix", normalMatrix);
	shaderProgram2->SetUniformMatrix("LightVPMatrix", camara2->GetViewProjection());
	meshFingers->Draw(GL_TRIANGLES);

	modelMatrix = geometria1->GetModelMatrix()*geometria3->GetModelMatrix()*geometria7->GetModelMatrix();
	normalMatrix = transpose(inverse(mat3(geometria1->GetModelMatrix()*geometria3->GetModelMatrix()*geometria7->GetModelMatrix())));
	shaderProgram2->SetUniformMatrix("mvpMatrix", camara1->GetViewProjection()*geometria1->GetModelMatrix()*geometria3->GetModelMatrix()*geometria7->GetModelMatrix());
	shaderProgram2->SetUniformMatrix("ModelMatrix", modelMatrix);
	shaderProgram2->SetUniformMatrix("NormalMatrix", normalMatrix);
	shaderProgram2->SetUniformMatrix("LightVPMatrix", camara2->GetViewProjection());
	meshFingers->Draw(GL_TRIANGLES);

	modelMatrix = geometria1->GetModelMatrix()*geometria4->GetModelMatrix()*geometria8->GetModelMatrix();
	normalMatrix = transpose(inverse(mat3(geometria1->GetModelMatrix()*geometria4->GetModelMatrix()*geometria8->GetModelMatrix())));
	shaderProgram2->SetUniformMatrix("mvpMatrix", camara1->GetViewProjection()*geometria1->GetModelMatrix()*geometria4->GetModelMatrix()*geometria8->GetModelMatrix());
	shaderProgram2->SetUniformMatrix("ModelMatrix", modelMatrix);
	shaderProgram2->SetUniformMatrix("NormalMatrix", normalMatrix);
	shaderProgram2->SetUniformMatrix("LightVPMatrix", camara2->GetViewProjection());
	meshFingers->Draw(GL_TRIANGLES);

	modelMatrix = geometria1->GetModelMatrix()*geometria5->GetModelMatrix()*geometria9->GetModelMatrix();
	normalMatrix = transpose(inverse(mat3(geometria1->GetModelMatrix()*geometria5->GetModelMatrix()*geometria9->GetModelMatrix())));
	shaderProgram2->SetUniformMatrix("mvpMatrix", camara1->GetViewProjection()*geometria1->GetModelMatrix()*geometria5->GetModelMatrix()*geometria9->GetModelMatrix());
	shaderProgram2->SetUniformMatrix("ModelMatrix", modelMatrix);
	shaderProgram2->SetUniformMatrix("NormalMatrix", normalMatrix);
	shaderProgram2->SetUniformMatrix("LightVPMatrix", camara2->GetViewProjection());
	meshFingers->Draw(GL_TRIANGLES);

	modelMatrix = geometria1->GetModelMatrix()*geometria6->GetModelMatrix()*geometria10->GetModelMatrix();
	normalMatrix = transpose(inverse(mat3(geometria1->GetModelMatrix()*geometria6->GetModelMatrix()*geometria10->GetModelMatrix())));
	shaderProgram2->SetUniformMatrix("mvpMatrix", camara1->GetViewProjection()*geometria1->GetModelMatrix()*geometria6->GetModelMatrix()*geometria10->GetModelMatrix());
	shaderProgram2->SetUniformMatrix("ModelMatrix", modelMatrix);
	shaderProgram2->SetUniformMatrix("NormalMatrix", normalMatrix);
	shaderProgram2->SetUniformMatrix("LightVPMatrix", camara2->GetViewProjection());
	meshFingers->Draw(GL_TRIANGLES);
	
	glActiveTexture(GL_TEXTURE0);
	myTexture1.Unbind();
	glActiveTexture(GL_TEXTURE1);
	myTexture2.Unbind();
	glActiveTexture(GL_TEXTURE2);
	myFramebuffer->UnbindDepthMap();

	shaderProgram2->Deactivate();


	shaderProgram1->Activate();
	// Geometría 2
	glActiveTexture(GL_TEXTURE0);
	myTexture3.Bind();
	glActiveTexture(GL_TEXTURE2);
	myFramebuffer->BindDepthMap();

	modelMatrix = geometria2->GetModelMatrix();
	normalMatrix = transpose(inverse(mat3(geometria2->GetModelMatrix())));
	shaderProgram1->SetUniformMatrix("mvpMatrix", camara1->GetViewProjection()*geometria2->GetModelMatrix());
	shaderProgram1->SetUniformMatrix("ModelMatrix", modelMatrix);
	shaderProgram1->SetUniformMatrix("NormalMatrix", normalMatrix);
	shaderProgram1->SetUniformMatrix("LightVPMatrix", camara2->GetViewProjection());
	meshPalma->Draw(GL_TRIANGLES);

	glActiveTexture(GL_TEXTURE0);
	myTexture3.Unbind();
	glActiveTexture(GL_TEXTURE2);
	myFramebuffer->UnbindDepthMap();

	shaderProgram1->Deactivate();
	

	/*
	// Activamos el vertexShader y el fragmentShader utilizando el manager
	//glUseProgram(shaderProgram);

	// Activamos el manager y en este momento se activan todos los VBOs asociados automáticamente
	//glBindVertexArray(vao);

	//glDrawArrays(GL_TRIANGLE_STRIP, 0, 12);ime

	// Terminamos de utilizar el manager
	//glBindVertexArray(0);

	// Desactivamos el manager
	//glUseProgram(0);
	*/

	//Cuando terminamos de renderear, cambiamos los buffers
	glutSwapBuffers();

	// Cambiando la tonalidad del fondo
	colour += 0.1;
	glClearColor(0.5 + 0.5*cos(radians(colour)), 0.5 + 0.5*sin(radians(colour)), sin(radians(colour))*cos(radians(colour)), 1.0f);
}

// Función que mueve la cámara dependiendo de la tecla presionada
void Keyboard(unsigned char key, int x, int y) {
	if (key == 'w')
		camara2->MoveForward(0.1f, false);
	if (key == 's')
		camara2->MoveForward(-0.1f, false);
	if (key == 'd')
		camara2->MoveRight(0.1f, false);
	if (key == 'a')
		camara2->MoveRight(-0.1f, false);
}

void SpecialKeys(int key, int x, int y) {
	if (key == GLUT_KEY_UP)
		camara2->MoveForward(0.1f, false);
	if (key == GLUT_KEY_DOWN)
		camara2->MoveForward(-0.1f, false);
	if (key == GLUT_KEY_RIGHT)
		camara2->Rotate(0.0f, 4.0f, 0.0f, true);
	if (key == GLUT_KEY_LEFT)
		camara2->Rotate(0.0f, -4.0f, 0.0f, true);
}

void Idle() {
	// Cuando OpenGL entra en modo Idle o de resposo (para guardar batería, por ejemplo)}
	// le decimos que vuelva a dibujar => vuelve a mandar a llamar GameLoop
	glutPostRedisplay();
}



int main(int argc, char* argv[]) {
	// Inicializar freeglut
	// Freeglut se encargfa de crear una ventana en donde podemos dibujar Gráficas Computacionales
	glutInit(&argc, argv);
	glutInitContextVersion(4, 4);


	// Iniciar el contexto de OpenGL, se refiere a las capacidades de la aplicación gráfica
	// En este caso se trabaja con el pipeline progamable
	glutInitContextProfile(GLUT_CORE_PROFILE);

	// Freeglut nos permite configurar eventos que ocurren en la ventana
	// Un evento que interesa es cuando alguien cierra la centana
	// En este caso, se deja de renderear la escena y se termina el programa
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	// También configuramos frambuffer, en este caso solicitamos un buffer
	// true color RGBA, un buffer de produndidad y un segundo buffer para renderear
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE); // Dos framebuffers

	// Iniciar las dimensiones de la ventana (en pixeles)
	glutInitWindowSize(800, 800);

	// Creeamos la ventana y le damos un título.
	glutCreateWindow("Título Súper Cool GL");

	glutDisplayFunc(GameLoop);

	// Asociamos una función para el cambio de la resolución de la ventana
	// FreeGlut la va a mandar a llamar cuando alguien cambie el tamaño de la ventana
	glutReshapeFunc(ReshapeWindow);

	// Cuando OpenGL entre en modo de reposo
	glutIdleFunc(Idle);

	// Avisar que existen la funciones que detectan el teclado
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKeys);

	// Inicializamos GLEW. Esta librería se encarga de obtener el API de OpenGL de nuestra tarjeta de video
	glewInit();

	// Configurar OpenGl. Este es el color por dedault del buffer de color en el framebuffer.
	glClearColor(1.0f, 1.0f, 0.5f, 1.0f);
	// Ademas de solicitar el buffer de profundidad, tenemos
	// que decirle a OpenGL que lo queremos activo
	glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LESS);
	// Activamos el borrado de caras traseras.
	// Ahora todos los triangulos que dibujemos deben estar en CCW
	//glEnable(GL_CULL_FACE);
	// No dibujar las caras traseras de las geometrías.
	//glCullFace(GL_BACK);
	//glFrontFace(GL_CW);

	cout << glGetString(GL_VERSION) << endl;

	// Inicializar DevIL. Esto se debe hacer sólo una vez.
	ilInit();
	// Cambiar el punto de origen de las texturas. Por default, DevIL
	// pone un punto de origen en la esquina superior izquierda.
	// Esto es compatible con el sistema operativo, pero no con el
	// funcionamiento de OpenGL. 
	ilEnable(IL_ORIGIN_SET);
	// Configurar el punto de origen de las texturas en la esquina
	// inferior izquierda
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Configuración inicial de nuestro programa
	Initialise();

	// Iniciar la aplicación. El Main se pausará en esta línea hasta que se cierre la ventana.
	glutMainLoop();

	return 0;
}
