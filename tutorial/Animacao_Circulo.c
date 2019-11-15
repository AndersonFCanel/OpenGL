#include <stdlib.h>
#include <math.h>
#include <glut.h>
#define PI 3.1415926535898
// Variáveis que guardam a translação que será aplicada 

GLfloat Tx;
GLfloat Ty;
GLint i;
GLfloat angle;

GLfloat cosseno;
GLfloat seno;


// Variáveis que guardam os valores mínimos de x e y 

GLfloat minX, maxX;
GLfloat minY, maxY;

// Variáveis que guardam o tamanho do incremento nas 
// direções x e y (número de pixels para se mover a 
// cada intervalo de tempo)
GLfloat xStep;
GLfloat yStep;

// Variáveis que guardam a largura e altura da janela
GLfloat windowXmin, windowXmax;
GLfloat windowYmin, windowYmax;

// Função callback de redesenho da janela de visualização
void Desenha(void)
{
	// Muda para o sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa a matriz de transformação corrente
	glLoadIdentity();

	// Limpa a janela de visualização com a cor  
	// de fundo definida previamente
	glClear(GL_COLOR_BUFFER_BIT);

	// Aplica uma translação sobre o objeto
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

// Função callback chamada quando o tamanho da janela é alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	GLsizei largura, altura;

	// Evita a divisao por zero
	if(h == 0) h = 1;

	// Atualiza as variáveis
	largura = w;
	altura = h;

	// Especifica as dimensões da Viewport
	glViewport(0, 0, largura, altura);

	// Inicializa o sistema de coordenadas de projeção
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Estabelece a janela de seleção (esquerda, direita, inferior, 
	// superior) mantendo a proporção com a janela de visualização
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

// Função callback chamada pela GLUT a cada intervalo de tempo
void Anima(int value)
{
	// Muda a direção quando chega na borda esquerda ou direita
	if( (Tx+maxX) > windowXmax || (Tx+minX) < windowXmin )
		xStep = -xStep;

	// Muda a direção quando chega na borda superior ou inferior
	if( (Ty+maxY) > windowYmax || (Ty+minY) < windowYmin )
		yStep = -yStep;


	// Move o objeto
	Tx += xStep;
	Ty += yStep;
	


	// Redesenha o objeto em outra posição
	glutPostRedisplay();
	glutTimerFunc(50,Anima, 1);
}

// Função callback chamada para gerenciar eventos de teclas
void Teclado (unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
}

// Função responsável por inicializar parâmetros e variáveis
void Inicializa (void)
{   
	// Define a cor de fundo da janela de visualização como branca
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// Inicialização das variáveis globais
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
    // Define do modo de operação da GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); 

	// Especifica a posição inicial da janela GLUT
	glutInitWindowPosition(100,100); 

	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(900,900); 

	// Cria a janela passando como argumento o título da mesma
	glutCreateWindow("Animacao");

	// Registra a função callback de redesenho da janela de visualização
	glutDisplayFunc(Desenha);

	// Registra a função callback de redimensionamento da janela de visualização
	glutReshapeFunc(AlteraTamanhoJanela);

	// Registra a função callback para tratamento das teclas ASCII
	glutKeyboardFunc (Teclado);

	// Registra a função callback que será chamada a cada intervalo de tempo
	glutTimerFunc(50, Anima, 1);

	// Chama a função responsável por fazer as inicializações 
	Inicializa();

	// Inicia o processamento e aguarda interações do usuário
	glutMainLoop();

	return 0;
}

