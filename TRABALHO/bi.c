#include <windows.h>  // for MS Windows
#include <glut.h>  // GLUT, include glu.h and gl.h
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>// necessário p/ as funções rand() e srand()
#include<time.h>//necessário p/ função time()


// Variáveis globais GL
GLfloat fAspect;
GLfloat angle = 0.0f;      // Rotação corrente
GLfloat x     = 0.0f;      // Valor de x corrente
GLfloat y     = 0.0f;      //Valor de y corrente
GLfloat cont  = 0.0f; 
 
//Variáveis para controle do jogo 
char     arrayCharCores           [5] = {'R','G','B','Y','W'};   //Identificadores das cores
int      arrayIntCores            [5] = {0, 1, 2, 3, 4};         //Identificadores numérico das cores
int      intCores                     = 999;                     //Variável para receber código proveniente do iedentificador de cores
GLfloat  corSelecionadaRGB        [3] = {1.0f,0.0f,0.0f};        //Vetor para armazenar informação sobre a cor corrente
GLfloat  corSelecionadaRGBAnterior[3] = {1.0f,0.0f,0.0f};        //Vetor para armazenar informação sobre a cor anterior
int      arrayDeJogadas           [255];                         //Vetor para armazenar Jogadas realizados pelo jogador
int      arrayDeQuebraCabeca	  [255];					     //Vetor para armazenar sequencia de cores a ser mermorizada pelo jogador
int      vez                          = 0;					     //Variável para armazenara vez corrente
int mudarCorSelecionadaRGBAnterior    = 0;                       //Variável para auxílio quando ocorrer mudança de cor


/**
* Função para montagem do quadrado conforme codgo de cor informado
* Esta função zera o valor das variáveis para que seja criado um novo quadrado.
*/
char remontaQuadrado(int color){

    char corSelecinada;
    int i = 0;
    
	switch (color) {
            case 0:
            	mudarCorSelecionadaRGBAnterior=1;
				if(mudarCorSelecionadaRGBAnterior == 1)   {
					corSelecionadaRGBAnterior[0] = corSelecionadaRGB[0];
				    corSelecionadaRGBAnterior[1] = corSelecionadaRGB[1];
					corSelecionadaRGBAnterior[2] = corSelecionadaRGB[2];
				    mudarCorSelecionadaRGBAnterior = 0;
  				}
                //printf("Vermelho");
                corSelecinada  = 'R';
                corSelecionadaRGB[0]=1.0f;
				corSelecionadaRGB[1]=0.0f;
				corSelecionadaRGB[2]=0.0f;
				cont = 0.0f;
				x    = 0.0f;
				y    = 0.0f;
				angle = 0.0f;
				intCores = 999;  //Para evitar loop infinito
			break;
            case 1:
            	mudarCorSelecionadaRGBAnterior=1;
				if(mudarCorSelecionadaRGBAnterior == 1)   {
					corSelecionadaRGBAnterior[0] = corSelecionadaRGB[0];
				    corSelecionadaRGBAnterior[1] = corSelecionadaRGB[1];
					corSelecionadaRGBAnterior[2] = corSelecionadaRGB[2];
				    mudarCorSelecionadaRGBAnterior = 0;
  				}
                //printf("Verde");
                corSelecinada = 'V';
				corSelecionadaRGB[0]=0.0f;
				corSelecionadaRGB[1]=1.0f;
				corSelecionadaRGB[2]=0.0f;
				cont = 0.0f;
				x    = 0.0f;
				y    = 0.0f;
				angle = 0.0f;
				intCores = 999;    //Para evitar loop infinito
				break;
            case 2:
            	mudarCorSelecionadaRGBAnterior=1;
				if(mudarCorSelecionadaRGBAnterior == 1)   {
					corSelecionadaRGBAnterior[0] = corSelecionadaRGB[0];
				    corSelecionadaRGBAnterior[1] = corSelecionadaRGB[1];
					corSelecionadaRGBAnterior[2] = corSelecionadaRGB[2];
				    mudarCorSelecionadaRGBAnterior = 0;
  				}
                //printf("Azul");
				corSelecinada = 'B';
				corSelecionadaRGB[0]=0.0f;
				corSelecionadaRGB[1]=0.0f;
				corSelecionadaRGB[2]=1.0f;
				cont = 0.0f;
				x    = 0.0f;
				y    = 0.0f;
				angle = 0.0f;
				intCores = 999;  //Para evitar loop infinito
				break;
            case 3:
            	mudarCorSelecionadaRGBAnterior=1;
				if(mudarCorSelecionadaRGBAnterior == 1)   {
					corSelecionadaRGBAnterior[0] = corSelecionadaRGB[0];
				    corSelecionadaRGBAnterior[1] = corSelecionadaRGB[1];
					corSelecionadaRGBAnterior[2] = corSelecionadaRGB[2];
				    mudarCorSelecionadaRGBAnterior = 0;
  				}
                //printf("Amarelo");
                corSelecinada = 'Y';
                corSelecionadaRGB[0]=1.0f;
				corSelecionadaRGB[1]=1.0f;
				corSelecionadaRGB[2]=0.0f;
                cont = 0.0f;
				x    = 0.0f;
				y    = 0.0f;
				angle = 0.0f;
				intCores = 999;  //Para evitar loop infinito
				
				break;
            case 4:
                mudarCorSelecionadaRGBAnterior=1;
				if(mudarCorSelecionadaRGBAnterior == 1)   {
					corSelecionadaRGBAnterior[0] = corSelecionadaRGB[0];
				    corSelecionadaRGBAnterior[1] = corSelecionadaRGB[1];
					corSelecionadaRGBAnterior[2] = corSelecionadaRGB[2];
				    mudarCorSelecionadaRGBAnterior = 0;
  				}
				//printf("Branco");
                corSelecinada = 'W';
                corSelecionadaRGB[0]=1.0f;
				corSelecionadaRGB[1]=1.0f;
				corSelecionadaRGB[2]=1.0f;
				cont = 0.0f;
				x    = 0.0f;
				y    = 0.0f;
				angle = 0.0f;
				intCores = 999;    //Para evitar loop infinito
				
				break;
            case 10:
            	intCores = 999;    //Para evitar loop infinito
				
				printf("VEZ: "+ vez) ;   
   				
   				printf("Jogada da rodada: ") ;//===>>> essa opção saíara
   				printf("\n");
	    		for(i=0; i< vez; i++){
				   Imprime(arrayDeJogadas[i]); //===>>> essa opção saíara  
   				}
   			break;
            
			default:
	        //	printf("Houve algum problema com o vetor de cores!");
				corSelecinada ='X';	
			    intCores = 999;    //Para evitar loop infinito
			break;	
		 }
         	 
   return  corSelecinada;

}

 
/* Initialize OpenGL Graphics */
void initGL() {
   // Set "clearing" or background color
   glClearColor(0.8f, 0.8f, 0.8f, 0.8f); // White and opaque  
}
 
/* Called back when there is no other event to be handled */
void idle() {
   glutPostRedisplay();   // Post a re-paint request to activate display()
}
 
/* Handler for window-repaint event. Call back when the window first appears and
   whenever the window needs to be re-painted. */
void desenha() {
	
   remontaQuadrado(intCores);
   	
   glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer
   glMatrixMode(GL_MODELVIEW);     // To operate on Model-View matrix
   glLoadIdentity();               // Reset the model-view matrix
 	
 	
   //Redesenhando o objeto anterior

	glPushMatrix();                     // Save model-view matrix setting
		//glTranslatef(-0.0f, 0.0f, 0.0f);    // Translate
		glRotatef(0.0f, 0.0f, 0.0f, 1.0f); // rotate by angle in degrees
		glBegin(GL_QUADS);                  // Each set of 4 vertices form a quad
		glColor3f( corSelecionadaRGBAnterior[0],
			       corSelecionadaRGBAnterior[1],
				   corSelecionadaRGBAnterior[2]);     
		glVertex2f(-0.5f, -0.5f);
		glVertex2f( 0.5f, -0.5f);
		glVertex2f( 0.5f,  0.5f);
		glVertex2f(-0.5f,  0.5f);
		glEnd();
	glPopMatrix();                      // Restore the model-view matrix	
 
   glPushMatrix();                     // Save model-view matrix setting
   //glTranslatef(-0.0f, 0.0f, 0.0f);    // Translate
   glRotatef(angle, 0.0f, 0.0f, 1.0f); // rotate by angle in degrees
   glBegin(GL_QUADS);                  // Each set of 4 vertices form a quad
      glColor3f( corSelecionadaRGB[0],
				 corSelecionadaRGB[1],
				 corSelecionadaRGB[2]);     
      glVertex2f(-x, -y);
      glVertex2f( x, -y);
      glVertex2f( x,  y);
      glVertex2f(-x,  y);
   glEnd();
   glPopMatrix();                      // Restore the model-view matrix
 
   glutSwapBuffers();   // Double buffered - swap the front and back buffers
   
 }
 
/* Handler for window re-size event. Called back when the window first appears and
   whenever the window is re-sized with its new width and height */
void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
   // Compute aspect ratio of the new window
   if (height == 0) height = 1;                // To prevent divide by 0
   GLfloat aspect = (GLfloat)width / (GLfloat)height;
 
   // Set the viewport to cover the new window
   glViewport(0, 0, width, height);
 
   // Set the aspect ratio of the clipping area to match the viewport
   glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
   glLoadIdentity();
   if (width >= height) {
     // aspect >= 1, set the height from -1 to 1, with larger width
      gluOrtho2D(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0);
   } else {
      // aspect < 1, set the width to -1 to 1, with larger height
     gluOrtho2D(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect);
   }
}

// Função callback chamada pela GLUT a cada intervalo de tempo
void Anima(int value)
{
	
	if( cont < 0.5f){
	  cont += 0.1f;
      x    += 0.1f;
      y    += 0.1f;
    }
   
   
   if(angle < 380.0f){
   
   		angle += 45.0f; 
 	}	


	// Redesenha o objeto em outra posição
	glutPostRedisplay();
	glutTimerFunc(300,Anima, 1);
}
 
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Evita a divisao por zero
	if(h == 0) h = 1;

	// Especifica as dimensões da Viewport
	glViewport(0, 0, w, h);

	// Calcula a correção de aspecto
	fAspect = (GLfloat)w/(GLfloat)h;

	EspecificaParametrosVisualizacao();
}
 
 // Função usada para especificar o volume de visualização
void EspecificaParametrosVisualizacao(void)
{
	// Especifica sistema de coordenadas de projeção
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de projeção
	glLoadIdentity();

	// Especifica a projeção perspectiva(angulo,aspecto,zMin,zMax)
	gluPerspective(angle,fAspect,0.5,500);

	//PosicionaObservador();
}
 
// Função callback chamada para gerenciar eventos de teclas normais
void Teclado (unsigned char key, int x, int y)  
{
	switch(key)
	{
		case 27:	exit(0);	// ESC ?
					break;
		case 'R':   //VERMELHO    
		    intCores = 0;
		    jogar(0);
		    montaQuebracabeca();
			break;
		case 'r':   //VERMELHO    
		    intCores = 0;
		    jogar(0);
		    montaQuebracabeca();
			break;	
		case 'G' :  //VERDE
			jogar(1);	
			intCores = 1;
			montaQuebracabeca();
			break;
		case 'g':  //VERDE
			jogar(1);	
			intCores = 1;
			montaQuebracabeca();
			break;
		case 'B':   //AZUL
			intCores = 2;
            jogar(2);
            montaQuebracabeca();
			break;
		case  'b':   //AZUL
			intCores = 2;
            jogar(2);
            montaQuebracabeca();
			break;	
		case 'Y':	//AMARELO
			intCores = 3;
		    jogar(3);
		    montaQuebracabeca();
			break;
		case 'y':	//AMARELO
			intCores = 3;
		    jogar(3);
		    montaQuebracabeca();
			break;	
		case 'W' :	//BRANCO
			intCores = 4;
		    jogar(4);
		    montaQuebracabeca();
			break;
		case 'w' :	//BRANCO
			intCores = 4;
		    jogar(4);
		    montaQuebracabeca();
			break;
		case 'i' :	//INFORMAR JOGADAS //===>>> essa opção saíara
			intCores = 10;
			break;	
		}
	glutPostRedisplay();
}


void jogar( int idCor, char cor){
    int i = 0;
    vez+=1;
    Set(&arrayDeJogadas [vez], idCor);
}

int checarCoincidenciaDosArrays(){
	int i=0;
	for(i=0; i< vez; i++){
		if(arrayDeJogadas[i] == arrayDeQuebraCabeca[i])	{
			
   		}else{
		   		printf("\nVoce errou a sequencia ");
		   		printf("\nSequencia informada pela maquina:  ");
	   			for(i=0; i< vez; i++){
				   Imprime(arrayDeQuebraCabeca[i]);	
				}   
			    printf("\nSequencia informada por voce:  ");
			    for(i=0; i< vez; i++){
				   Imprime(arrayDeJogadas[i]);	
				} 
				break;
		   }	   
	}
}


void montaQuebracabeca(void){
	int i = 0;
	srand(time(NULL));
	printf("\nQuebra Cabeca: ");//===>>> essa opção saíara
	int valorRandomico = 0;
	
	if(vez != 0){
	 do{	
		valorRandomico = rand() % 5;
		Set(&arrayDeQuebraCabeca[vez], valorRandomico);	
	  }while(valorRandomico == arrayDeQuebraCabeca[vez-1] );
	}else{
		do{	
		valorRandomico = rand() % 5;
		Set(&arrayDeQuebraCabeca[vez], valorRandomico);	
	  }while(valorRandomico == arrayDeQuebraCabeca[vez] );
	}
	
	for(i=0; i<= vez; i++){
		 Imprime(arrayDeQuebraCabeca[i]);	   //===>>> essa opção saíara
   	}	
}

void Set (int *N, int i) // função com um parâmetro por referência
{
  *N = i;
}

 void Imprime (int N) // função com um parâmetro por valor
{
    printf("%d", N);
}
 
/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {

	if(vez = 0){
		montaQuebracabeca();
	}

    // Define o modo de operação da GLUT
    glutInit(&argc, argv);             // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE);  // Enable double buffered mode
    
	// Especifica o tamanho inicial em pixels da janela GLUT
    glutInitWindowSize(640, 480);   // Set the window's initial width & height - non-square
   
	// Especifica a posição inicial da janela GLUT
	glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
    
	// Cria a janela passando como argumento o título da mesma
	glutCreateWindow("Jogo da memória");
 
	// Registra a função callback de redesenho da janela de visualização
	glutDisplayFunc(desenha);
   
   	// Register callback handler for window re-size event
    glutReshapeFunc(reshape);       
  
    // Register callback handler if no other event
    glutIdleFunc(idle);           
    
    // Chama a função responsável por fazer as inicializações 
	//Inicializa();
 	initGL();                       // Our own OpenGL initialization 
    
	// Registra a função callback que será chamada a cada intervalo de tempo
	glutTimerFunc(50, Anima, 1);
  
	  
	// Registra a função callback de redimensionamento da janela de visualização
 	glutReshapeFunc(AlteraTamanhoJanela);

	// Registra a função callback para tratamento das teclas ASCII
 	glutKeyboardFunc (Teclado);

	// Registra a função callback para tratamento das teclas especiais
//	glutSpecialFunc (TeclasEspeciais);

	// Registra a função callback para eventos de botões do mouse	
//	glutMouseFunc(GerenciaMouse);
	 
	// Registra a função callback para eventos de movimento do mouse	
//	glutMotionFunc(GerenciaMovim);


	// Inicia o processamento e aguarda interações do usuário
	glutMainLoop();
 
	return 0;

}
