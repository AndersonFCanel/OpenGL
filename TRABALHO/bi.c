#include <windows.h>  // for MS Windows
#include <glut.h>  // GLUT, include glu.h and gl.h
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>// necessário p/ as funções rand() e srand()
#include<time.h>//necessário p/ função time()

/* Jogo da memória tipo genius,
* INTRUÇÕES E TECLAS PARA O JOGO: 
* Guardar sequências de cores e depois repeti-las através das teclas correspondentes:

* R / r -  Vermelho
* G / g -  Verde
* B / b -  Azul
* Y / y -  Amarelo
* W / w -  Branco
*
* Quando digitar a sequência anterior completa, pressionar S para próxima etapa. 
* Para Iniciar próxima rodada pressionar S / s.
*/


// Variáveis globais GL
GLfloat fAspect;
GLfloat angle = 0.0f;      // Rotação corrente
GLfloat x     = 0.0f;      // Valor de x corrente
GLfloat y     = 0.0f;      //Valor de y corrente
GLfloat contPassoDesenho  = 0.0f; 
 
//Variáveis para controle do jogo 
//Identificador das cores
char     arrayCharCores           [5] = {'R','G','B','Y','W'};   //Identificadores das cores
int      arrayIntCores            [5] = {0, 1, 2, 3, 4};         //Identificadores numérico das cores
int      idCor                    ;                          //Variável para receber código proveniente do iedentificador de cores

//RGB dos objetos
GLfloat  corSelecionadaRGB        [3] = {0.0f,0.0f,0.0f};        //Vetor para armazenar informação sobre a cor corrente
GLfloat  corSelecionadaRGBAnterior[3] = {0.8f,0.8f,0.8f};        //Vetor para armazenar informação sobre a cor anterior

//Translação do texto
GLfloat tx = -0.6f; 


int      arrayDeJogadas                [255];                     //Vetor para armazenar Jogadas realizados pelo jogador
int      arrayDeGuardaSequenciaDeCores [255];                     //Vetor para armazenar sequencia de cores a ser mermorizada pelo jogador

//Controladores
int      exibirSequenciaMemorizavel     = 0;                     //Variável para saber se é para informar gráficamente ao jogador a existência de nova rodada
int      aguardandoJogadas              = 0;
int      gameover                       = 0;                     //essa é obivia
int      exibirMenssagemJogar           = 0; 

//Contadores
int      vez                            = 0;                     //Variável para armazenara vez corrente
int      contIteracaoNaRodadaCorrente   = 0;                     //Variável responsável pela contagem do loop corrente até que se inicie uma nova rodada
int      contJogadaCorrente             = 0;
int      contSizeArrayDeJogada          = 0;
int      contSizeGuardaSequenciaDeCores = 0;


/**
* Função para montagem do quadrado conforme código de cor informado
* Esta função zera o valor das variáveis para que seja criado um novo quadrado.
*/
char remontaQuadrado(int color){

    char corSelecinada;
    int i = 0;
    
    switch (color) {
            case 0:
       
                    corSelecionadaRGBAnterior[0] = corSelecionadaRGB[0];
                    corSelecionadaRGBAnterior[1] = corSelecionadaRGB[1];
                    corSelecionadaRGBAnterior[2] = corSelecionadaRGB[2];
                
                //printf("Vermelho");
                corSelecinada  = 'R';
                corSelecionadaRGB[0]=1.0f;
                corSelecionadaRGB[1]=0.0f;
                corSelecionadaRGB[2]=0.0f;
                contPassoDesenho = 0.0f;
                x    = 0.0f;
                y    = 0.0f;
                angle = 0.0f;
                idCor = 9;  //Para evitar loop infinito
            break;
            case 1:
                    corSelecionadaRGBAnterior[0] = corSelecionadaRGB[0];
                    corSelecionadaRGBAnterior[1] = corSelecionadaRGB[1];
                    corSelecionadaRGBAnterior[2] = corSelecionadaRGB[2];
                
				//printf("Verde");
                corSelecinada = 'G';
                corSelecionadaRGB[0]=0.0f;
                corSelecionadaRGB[1]=1.0f;
                corSelecionadaRGB[2]=0.0f;
                contPassoDesenho = 0.0f;
                x    = 0.0f;
                y    = 0.0f;
                angle = 0.0f;
                idCor = 9;    //Para evitar loop infinito
                break;
            case 2:
                    corSelecionadaRGBAnterior[0] = corSelecionadaRGB[0];
                    corSelecionadaRGBAnterior[1] = corSelecionadaRGB[1];
                    corSelecionadaRGBAnterior[2] = corSelecionadaRGB[2];
                
				//printf("Azul");
                corSelecinada = 'B';
                corSelecionadaRGB[0]=0.0f;
                corSelecionadaRGB[1]=0.0f;
                corSelecionadaRGB[2]=1.0f;
                contPassoDesenho = 0.0f;
                x    = 0.0f;
                y    = 0.0f;
                angle = 0.0f;
                idCor = 9;  //Para evitar loop infinito
                break;
            case 3:
                
				    corSelecionadaRGBAnterior[0] = corSelecionadaRGB[0];
                    corSelecionadaRGBAnterior[1] = corSelecionadaRGB[1];
                    corSelecionadaRGBAnterior[2] = corSelecionadaRGB[2];
                
				//printf("Amarelo");
                corSelecinada = 'Y';
                corSelecionadaRGB[0]=1.0f;
                corSelecionadaRGB[1]=1.0f;
                corSelecionadaRGB[2]=0.0f;
                contPassoDesenho = 0.0f;
                x    = 0.0f;
                y    = 0.0f;
                angle = 0.0f;
                idCor = 9;  //Para evitar loop infinito
                
                break;
            case 4:
                
				    corSelecionadaRGBAnterior[0] = corSelecionadaRGB[0];
                    corSelecionadaRGBAnterior[1] = corSelecionadaRGB[1];
                    corSelecionadaRGBAnterior[2] = corSelecionadaRGB[2];
                
				//printf("Branco");
                corSelecinada = 'W';
                corSelecionadaRGB[0]=1.0f;
                corSelecionadaRGB[1]=1.0f;
                corSelecionadaRGB[2]=1.0f;
                contPassoDesenho = 0.0f;
                x    = 0.0f;
                y    = 0.0f;
                angle = 0.0f;
                idCor = 9;    //Para evitar loop infinito
                
                break;
            
            default:
            //  printf("Houve algum problema com o vetor de cores!");
                corSelecinada ='X'; 
                idCor = 9;    //Para evitar loop infinito
            break;  
         }
             
   return  corSelecinada;

}

 
/* Inicializa OpenGL Graphics */
void initGL() {
   // Set "clearing" or background color
   glClearColor(0.8f, 0.8f, 0.8f, 0.8f); // White and opaque  
        
}
 
/* Called back quando não há outro evento a ser tratado */
void idle() {
   glutPostRedisplay();   //Poste uma solicitação de nova pintura para ativar display()
}
 
/* Manipulador para evento de repintar janelas. Callback quando a janela aparecer pela primeira vez e
   sempre que a janela precisar ser pintada novamente. */
void desenha() {
    
   remontaQuadrado(idCor);
    
   glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer
   glMatrixMode(GL_MODELVIEW);     // To operate on Model-View matrix
   glLoadIdentity();               // Reset the model-view matrix
    
    if(contIteracaoNaRodadaCorrente > 0 || vez == 0  ){
	
	//mensagem de Here go
    if(vez == 0 ){
        glPushMatrix();
          glBegin(GL_QUADS);
              glColor3f ( 0.0f,  0.0f,  0.0f);
                glVertex2f(-0.9f, 0.6f);
                glVertex2f( 0.9f,  0.6f);
                glVertex2f( 0.9f, 0.9f);
                glVertex2f(-0.9f,  0.9f);
          glEnd();
        glPopMatrix();
        
        glPushMatrix();
           glTranslatef(-0.4f, 0.7f, 0.0f);
           glScalef(0.001f, 0.001f, 0.0);
           DesenhaTexto("HERE WE GO", 1.0f,1.0f,1.0f);
        glPopMatrix();
    }
    
    //Redesenhando o objeto anterior
    if(vez > 0 && contIteracaoNaRodadaCorrente >1){
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
    }

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
   
    //mensagem para jogador entrar com os dados
    if(exibirMenssagemJogar == 1 && vez > 0){
    
        
        glPushMatrix();
          glBegin(GL_QUADS);
              glColor3f ( 0.0f,  0.0f,  0.0f);
                glVertex2f(-0.6f, 0.6f);
                glVertex2f( 0.6f,  0.6f);
                glVertex2f( 0.6f, 0.9f);
                glVertex2f(-0.6f,  0.9f);
          glEnd();
        glPopMatrix();
        
        glPushMatrix();
           //glTranslatef(-0.2f, 0.4f, 0.0f);
           glTranslatef( tx, 0.7f, 0.0f);   
           glScalef(0.001f, 0.001f, 0.0);
           DesenhaTexto("ENJOY", 1.0f,1.0f,1.0f);
        glPopMatrix();
        
        tx+=0.0001f;
        
        if(tx >= 0.22f){
            tx = -0.6f;
        }
        
    }
   
    //mensagem de gamer over
    if(gameover == 1){
        glPushMatrix();
          glBegin(GL_QUADS);
              glColor3f ( 0.0f,  0.0f,  0.0f);
                glVertex2f(-0.6f, -0.6f);
                glVertex2f( 0.6f, -0.6f);
                glVertex2f( 0.6f,  0.6f);
                glVertex2f(-0.6f,  0.6f);
          glEnd();
        glPopMatrix();
        
        glPushMatrix();
           glTranslatef(-0.3f, 0.0f, 0.0f);
           glScalef(0.001f, 0.001f, 0.0);
           DesenhaTexto("GAMEOVER", 1.0f,1.0f,1.0f);
        glPopMatrix();
    }      
    }
  
   glutSwapBuffers();   // Double buffered - swap the front and back buffers
   
 }
 
//funcao que escreve texto na tela
void DesenhaTexto(char *string, float r, float g, float b)
{  
        glColor3f(r, g, b);
        // Posição no universo onde o texto será colocado          

        // Exibe caracter a caracter
        while(*string)
             glutStrokeCharacter(GLUT_STROKE_ROMAN,*string++);
} 
 
 
 
/* Manipulador para evento de redimensionamento de janela. Chamado de volta quando a janela aparece pela primeira vez e
   sempre que a janela for redimensionada com sua nova largura e altura */
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
    
    if( contPassoDesenho < 0.5f){
      contPassoDesenho += 0.05f;
      x    += 0.05f;
      y    += 0.05;
    }
   
   
    if(angle < 380.0f){
         angle += 45.0f; 
    }   

   
    if((contIteracaoNaRodadaCorrente <= vez && contPassoDesenho >= 0.5f || exibirSequenciaMemorizavel >=1 ) && gameover == 0 ){
       // glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer
			printf("\naguardandoJogadas: %d",aguardandoJogadas);
			
			if(aguardandoJogadas==0){
				
				imprimeQuebraCabeca(arrayDeGuardaSequenciaDeCores[contIteracaoNaRodadaCorrente]);
		        printf("\nContagem LOOP corrente: %d",contIteracaoNaRodadaCorrente);
		        printf(" - Codigo da cor a ser exibida: %d",arrayDeGuardaSequenciaDeCores[contIteracaoNaRodadaCorrente]);
		        printf(" - VEZ: %d",vez);   
		        
		        if( contIteracaoNaRodadaCorrente == vez ){
		            exibirSequenciaMemorizavel = 0;
		            exibirMenssagemJogar = 1;
		        }
		        
		        x    = 0.5f;
		        y    = 0.5f;
		        
		        //printf(" \n- Codigo da cor informada pelo usuario: %d",arrayDeJogadas[contIteracaoNaRodadaCorrente]);
		        
				contIteracaoNaRodadaCorrente++;
				
			}
    }

//  printf("TESTE");

    // Redesenha o objeto em outra posição
    glutPostRedisplay();
    glutTimerFunc(250,Anima, 1);
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
 
void reset (){
	int i = 0;
	int valorRandomico = 0;
	srand(time(NULL));
	
	for(i=0; i< 255; i++){
		//arrayDeGuardaSequenciaDeCores[i] = 9; 	   //===>>> essa opção saíara
		arrayDeJogadas[i] = NULL;
		
		if(i > 0){
     	do{    
        	valorRandomico = rand() % 5;
			Set(&arrayDeGuardaSequenciaDeCores[i], valorRandomico);
       }while(valorRandomico == arrayDeGuardaSequenciaDeCores[i-1] );
			}else
		{   
	     	 valorRandomico = rand() % 5;
	      	Set(&arrayDeGuardaSequenciaDeCores[i], valorRandomico); 
		}
	}
	
	vez = 0;
	exibirSequenciaMemorizavel = 0;
	gameover = 0;
		
	corSelecionadaRGBAnterior[0] = 1;
	corSelecionadaRGBAnterior[1] = 0 ;
	corSelecionadaRGBAnterior[2] = 0;

	corSelecionadaRGB[0]=1.0f;
	corSelecionadaRGB[1]=0.0f;
	corSelecionadaRGB[2]=0.0f;
	
	exibirMenssagemJogar = 0;
					
	contPassoDesenho = 0.0f;
	x    = 0.0f;
	y    = 0.0f;
	angle = 0.0f;
	idCor = 9;    //Para evitar loop infinito
	
	contIteracaoNaRodadaCorrente   = 0;                     //Variável responsável pela contagem do loop corrente até que se inicie uma nova rodada
    contJogadaCorrente             = 0;
	aguardandoJogadas = 0;

	
}
 
void executaRotinaGame(int n) {
		contIteracaoNaRodadaCorrente = 0;
		exibirMenssagemJogar = 0;
	    
		aguardandoJogadas = 1;
	    idCor = n;                //Set cor 			
	
		jogar(n);                    //ALimenta arrayDeJogadas
	
		checarCoincidenciaDosArrays();
	    //vez++;
		//montaSequenciaMemorizavel();
	}
 
// Função callback chamada para gerenciar eventos de teclas normais
void Teclado (unsigned char key, int x, int y)  
{
    
	int i = 0;
    
//	if( gameover == 0 ){
    
		switch(key)
		{
			case 27:    exit(0);    // ESC ?
						break;
			case 'R':   //VERMELHO    
				//montaSequenciaMemorizavel();         // Cria jogada randomica
			executaRotinaGame(0); 
				break;
			case 'r':   //VERMELHO    
				//montaSequenciaMemorizavel();
				executaRotinaGame(0); 
				break;  
			case 'G' :  //VERDE
				//montaSequenciaMemorizavel();
				executaRotinaGame(1); 
				break;
			case 'g':  //VERDE
				//montaSequenciaMemorizavel();
			executaRotinaGame(1); 
				break;
			case 'B':   //AZUL
				//montaSequenciaMemorizavel();
			executaRotinaGame(2);
				break;
			case  'b':   //AZUL
				//montaSequenciaMemorizavel();
				executaRotinaGame(2);
				break;  
			case 'Y':   //AMARELO
				//montaSequenciaMemorizavel();
				executaRotinaGame(3);
				break;
			case 'y':   //AMARELO
				//montaSequenciaMemorizavel();
				executaRotinaGame(3);
				break;  
			case 'W' :  //BRANCO
				//montaSequenciaMemorizavel();
				executaRotinaGame(4);
				break;
			case 'w' :  //BRANCO
				executaRotinaGame(4);
				//montaSequenciaMemorizavel()
				break;
			case 'S' :  //INFORMAR JOGADAS //===>>> essa opção saíara
				idCor = 9;
				exibirSequenciaMemorizavel = 1;
				gameover = 0;
				exibirMenssagemJogar = 0;
				break;
			case 's' :  //INFORMAR JOGADAS //===>>> essa opção saíara
				idCor = 9;
				exibirSequenciaMemorizavel = 1;
				gameover = 0;
				break;
			case 'N' :  //NEW GAME
			
			reset ();
				
				break;      
			case 'i' :  //INFORMAR JOGADAS //===>>> essa opção saíara
				idCor = 10;
				break;  
			}
    glutPostRedisplay();
}


void jogar( int idCorInfo, char cor){
    int i = 0;
   
	Set(&arrayDeJogadas [contJogadaCorrente], idCorInfo);
	contJogadaCorrente +=1;
	/*if(contJogadaCorrente == vez){
		
		aguardandoJogadas=0;
	}else{
		aguardandoJogadas = 1;
	}*/

}

int checarCoincidenciaDosArrays(){
    int i=0;

    printf("\ncontJogadasCorrente: %d",contJogadaCorrente);
    printf("\nvez: %d",vez);

	if(contJogadaCorrente >= vez){
		aguardandoJogadas=0;
		contJogadaCorrente =0;
		vez++;
	}else{
		aguardandoJogadas = 1;
	}
	
 if(aguardandoJogadas == 1){
 
    do{
    	printf("\nI: %d",i);
	        if(arrayDeJogadas[i] == arrayDeGuardaSequenciaDeCores[i]) {
	             gameover = 0;
	             printf("\nVoce acertou a sequencia ate aqui!");
	        }else{
	                printf("\nVoce errou a sequencia ");
	                printf("\nSequencia informada pela maquina:  ");
	                for(i=0; i<= vez; i+=1){
	                   Imprime(arrayDeGuardaSequenciaDeCores[i]); 
	                }   
	                printf("\nSequencia informada por voce:  ");
	                for(i=0; i<= vez; i++){
	                   Imprime(arrayDeJogadas[i]);  
	                } 
	                gameover = 1;
	                return 0;
	           }       
			i++;	
//	}while( i<vez );	
	}while( i<contJogadaCorrente );
}

    return 1;
}


void Set (int *N, int i) // função com um parâmetro por referência
{
	printf("\nEntrou com: %d", i);
  *N = i;
}

 void Imprime (int N) // função com um parâmetro por valor
{
    printf("%d", N);
}
 
void imprimeQuebraCabeca(int codColor){
        switch(codColor)
    {
        case 0:   //VERMELHO    
            idCor = 0;
            break;
        case 1 :  //VERDE
            idCor = 1;
            break;
        case 2 :   //AZUL
            idCor = 2;
            break;  
        case 3 :    //AMARELO
            idCor = 3;
            break;  
        case 4 :    //BRANCO
            idCor = 4;
            break;
        }
    glutPostRedisplay();
    
}
 
 
/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {

    if(vez == 0){
        reset();
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
//  glutSpecialFunc (TeclasEspeciais);

    // Registra a função callback para eventos de botões do mouse   
//  glutMouseFunc(GerenciaMouse);
     
    // Registra a função callback para eventos de movimento do mouse    
//  glutMotionFunc(GerenciaMovim);


    // Inicia o processamento e aguarda interações do usuário
    glutMainLoop();
 
    return 0;

}
