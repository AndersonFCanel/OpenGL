#include <glut.h>
// -lglut32 -lglu32 -lopengl32

void desenha()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
	
}



int main(int argc, char* argv[]) {

	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Ola Mundo");
	glClearColor(0, 0, 0, 0);
	glutDisplayFunc(desenha);
    
          	
	glutMainLoop();
	return 0;
}
