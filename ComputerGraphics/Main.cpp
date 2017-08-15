#include <GL/glew.h>
#include <GL/freeglut.h>

void GameLoop() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// WARNING!!!!!! ESTO ES OPENGL VIEJITO!!!!!!

	glBegin(GL_TRIANGLES);
	
	//-1 para borde izquierdo, 1 para borde derecho, 0 centro, 1 arriba, -1 abajo
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(-1.0f, -1.0f); // SOlo dos coordenadas, x y y , dos puntos o z para 3D pero este no tiene profundidad

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2d(1.0f, -1.0f);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2d(0.0f, 1.0f);

	glEnd();

	glutSwapBuffers();
}

int main_1(int argc, char* argv[]) {
	// Inicializar freeglut
	// Freeglut se encargfa de crear una ventana en donde podemos dibujar Gráficas Computacionales
	glutInit(&argc, argv);
	
	// Iniciar el contexto de OpenGL, se refiere a las capacidades de la aplicación gráfica
	// En este caso se trabaja con el pipeline clásico
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	
	// Freeglut nos permite configurar eventos que ocurren en la ventana
	// Un evento que interesa es cuando alguien cierra la centana
	// En este caso, se deja de renderear la escena y se termina el programa
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	// También configuramos frambuffer, en este caso solicitamos un buffer
	// true color RGBA, un buffer de produndidad y un segundo buffer para renderear
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE); // Dos framebuffers

	// Iniciar las dimensiones de la ventana (en pixeles)
	glutInitWindowSize(400, 400);

	// Creeamos la ventana y le damos un título.
	glutCreateWindow("Título Genial GL");

	glutDisplayFunc(GameLoop);

	// Inicializamos GLEW. Esta librería se encarga de obtener el API de OpenGL de nuestra tarjeta de video
	glewInit();

	// Configurar OpenGl. Este es el color por dedault del buffer de color en el framebuffer.
	glClearColor(1.0f, 1.0f, 0.5f, 1.0f);

	// Iniciar la aplicación. El Main se pausará en esta línea hasta que se cierre la ventana.
	glutMainLoop();

	return 0;
}