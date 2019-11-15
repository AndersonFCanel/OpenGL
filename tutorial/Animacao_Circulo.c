#include <stdlib.h>
#include <math.h>
#include <glut.h>
#define PI 3.1415926535898
// Vari�veis que guardam a transla��o que ser� aplicada 

GLfloat Tx;
GLfloat Ty;
GLint i;
GLfloat angle;

GLfloat cosseno;
GLfloat seno;


// Vari�veis que guardam os valores m�nimos de x e y 

GLfloat minX, maxX;
GLfloat minY, maxY;

// Vari�veis que guardam o tamanho do incremento nas 
// dire��es x e y (n�mero de pixels para se mover a 
// cada intervalo de tempo)
GLfloat xStep;
GLfloat yStep;

// Vari�veis que guardam a largura e altura da janela
GLfloat windowXmin, windowXmax;
GLfloat windowYmin, windowYmax;

// Fun��o callback de redesenho da janela de visualiza��o
void Desenha(void)
{
	// Muda para o sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa a matriz de transforma��o corrente
	glLoadIdentity();

	// Limpa a janela de visualiza��o com a cor  
	// de fundo definida previamente
	glClear(GL_COLOR_BUFFER_BIT);

	// Aplica uma transla��o sobre o objeto
	glTranslatef(Tx, Ty, 0.0f);
	

	glScalef(5.0f, 5.0f, 0.0f);

GLfloat circle_points = 100;

glBegin(GL_LINE_LOOP);
	for (i = 0; i < circle_points; i++){
		glColor3f(1.0f, 1.0f, 0.0f);
		angle = 2*PI*i/circle_points;
		glVertex2f(cos(angle), sin(angle));
	}
glEnd();

	// Executa os comandos OpenGL 
	glutSwapBuffers();
}

// Fun��o callback chamada quando o tamanho da janela � alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	GLsizei largura, altura;

	// Evita a divisao por zero
	if(h == 0) h = 1;

	// Atualiza as vari�veis
	largura = w;
	altura = h;

	// Especifica as dimens�es da Viewport
	glViewport(0, 0, largura, altura);

	// Inicializa o sistema de coordenadas de proje��o
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Estabelece a janela de sele��o (esquerda, direita, inferior, 
	// superior) mantendo a propor��o com a janela de visualiza��o
	if (largura <= altura) 
	{
		gluOrtho2D (-40.0f, 40.0f, -40.0f*altura/largura, 40.0f*altura/largura);
		windowXmin = -40.0f;
		windowXmax =  40.0f;
		windowYmin = -40.0f*altura/largura;
		windowYmax = 40.0f*altura/largura;
	}
	else
	{ 
		gluOrtho2D (-40.0f*largura/altura, 40.0f*largura/altura, -40.0f, 40.0f);
		windowXmin = -40.0f*largura/altura;
		windowXmax =  40.0f*largura/altura;
		windowYmin = -40.0f;
		windowYmax =  40.0f;
	}
}

// Fun��o callback chamada pela GLUT a cada intervalo de tempo
void Anima(int value)
{
	// Muda a dire��o quando chega na borda esquerda ou direita
	if( (Tx+maxX) > windowXmax || (Tx+minX) < windowXmin )
		xStep = -xStep;

	// Muda a dire��o quando chega na borda superior ou inferior
	if( (Ty+maxY) > windowYmax || (Ty+minY) < windowYmin )
		yStep = -yStep;


	// Move o objeto
	Tx += xStep;
	Ty += yStep;
	


	// Redesenha o objeto em outra posi��o
	glutPostRedisplay();
	glutTimerFunc(50,Anima, 1);
}

// Fun��o callback chamada para gerenciar eventos de teclas
void Teclado (unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
}

// Fun��o respons�vel por inicializar par�metros e vari�veis
void Inicializa (void)
{   
	// Define a cor de fundo da janela de visualiza��o como branca
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// Inicializa��o das vari�veis globais
	xStep = yStep = 1.0f;
	Tx = Ty = 0.0f;
	minX = -6.0f;
	maxX =  6.0f;
	minY = -6.0f;
	maxY =  6.0f;
	windowXmin = windowYmin = -40.0f;
	windowXmax = windowYmax = 40.0f;
}

// Programa Principal 
int main(void)
{
    // Define do modo de opera��o da GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); 

	// Especifica a posi��o inicial da janela GLUT
	glutInitWindowPosition(100,100); 

	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(900,900); 

	// Cria a janela passando como argumento o t�tulo da mesma
	glutCreateWindow("Animacao");

	// Registra a fun��o callback de redesenho da janela de visualiza��o
	glutDisplayFunc(Desenha);

	// Registra a fun��o callback de redimensionamento da janela de visualiza��o
	glutReshapeFunc(AlteraTamanhoJanela);

	// Registra a fun��o callback para tratamento das teclas ASCII
	glutKeyboardFunc (Teclado);

	// Registra a fun��o callback que ser� chamada a cada intervalo de tempo
	glutTimerFunc(50, Anima, 1);

	// Chama a fun��o respons�vel por fazer as inicializa��es 
	Inicializa();

	// Inicia o processamento e aguarda intera��es do usu�rio
	glutMainLoop();

	return 0;
}

