#include <stdlib.h>
#include <glut.h>
#include <string>
#include <math.h>

#define LARGURA 500 //LARGURA DA JANELA
#define ALTURA 500 //ALTURA DA JANELA
#define PI 3.14 //Pi
#define DISTANCIA_CORTE_PAREDE 10 //distancia do inicio da linha de corte da parede

int janelaGeral;
int cordenadasCamposJogada[9][2] = {
	{0,(ALTURA/3)*2},	{LARGURA/3,(ALTURA/3)*2},	{(LARGURA/3)*2,(ALTURA/3)*2},
	{0,ALTURA/3},		{LARGURA/3,ALTURA/3},		{(LARGURA/3)*2,ALTURA/3},
	{0,0},				{LARGURA/3,0},			{(LARGURA/3)*2,0}
};

//campo marcado{0=nenhum;1=X;2=O}
int campoMarcado[9] = {0,0,0,0,0,0,0,0,0}; 

int i;
int VEZ = 1; //1 = X| -1 = O
int XVence=0,OVence=0;
int linha=0;
int coluna=0;
int calc = 0;
int marcaVencedor = 0; //identifica qual linha desenhar
int vencedor = 0;
int cordenadasLinhasVencedor[8][4] = {
	//cordenadas das linhas para desenhar quando houver vencedor
	//{x0,y0,x,y}
	{ (LARGURA/3)/2 , DISTANCIA_CORTE_PAREDE , (LARGURA/3)/2 , ALTURA - DISTANCIA_CORTE_PAREDE}, // | viória na coluna 1
	{ (LARGURA/2) , DISTANCIA_CORTE_PAREDE , (LARGURA/2) , ALTURA - DISTANCIA_CORTE_PAREDE}, // | viória na coluna 2
	{ LARGURA - (LARGURA/3)/2 , DISTANCIA_CORTE_PAREDE , LARGURA - (LARGURA/3)/2 , ALTURA - DISTANCIA_CORTE_PAREDE}, // | viória na coluna 2
	
	{ DISTANCIA_CORTE_PAREDE , ALTURA - (ALTURA/3)/2, LARGURA - DISTANCIA_CORTE_PAREDE, ALTURA - (ALTURA/3)/2}, // -- viória na linha 1
	{ DISTANCIA_CORTE_PAREDE , (ALTURA/2), LARGURA - DISTANCIA_CORTE_PAREDE, ALTURA/2}, // -- viória na linha 2
	{ DISTANCIA_CORTE_PAREDE , (ALTURA/3)/2, LARGURA - DISTANCIA_CORTE_PAREDE, (ALTURA/3)/2}, // -- viória na linha 3

	{ DISTANCIA_CORTE_PAREDE , ALTURA - DISTANCIA_CORTE_PAREDE, LARGURA - DISTANCIA_CORTE_PAREDE, DISTANCIA_CORTE_PAREDE}, // [\] viória na transversal
	{ DISTANCIA_CORTE_PAREDE , DISTANCIA_CORTE_PAREDE, LARGURA - DISTANCIA_CORTE_PAREDE, ALTURA-DISTANCIA_CORTE_PAREDE}, // [/] viória na transversal
};


/*
 *  Definicao das funcoes
 */
void init(void);
void display(void);
void keyboard(unsigned char key, int x, int y); //capta as acoes no teclado
void mouse(int button, int state, int x, int y); //campta as acoes do mouse
void desenhaO(GLfloat x, GLfloat y); //desenha jogadorO
void desenhaX(int x, int y); //Desenha jogadorX
int descobreColuna(int x);
int descobreLinha(int y);
void resetarJogo(void);
void showMenu(void); 
void verificaVencedor(void);
void verPontos(void);



int main(int argc, char** argv){
	glutInit(&argc, argv);
	// glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (LARGURA, ALTURA);
	glutInitWindowPosition (100, 100); 

	glutCreateWindow ("Jogo-da-Velha-Trabalho de computação gráfica");
	showMenu();
	init();
	
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);	
	glutMouseFunc(mouse);
	
	glutMainLoop();
	return 0;
}

void init(void){
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glOrtho (0, LARGURA, 0, ALTURA, -1 ,1);
}

void display(void){
	glClear(GL_COLOR_BUFFER_BIT);

	// glPolygonMode(GL_BACK, GL_LINE);
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(15.0);

	//MARGENS DO CAMPO
	glColor3f(1.0, 1.0, 1.0);
	//VERTICAL
	glBegin(GL_LINES); glVertex2i(LARGURA/3,ALTURA-1);  glVertex2i(LARGURA/3,1); glEnd();
	glBegin(GL_LINES); glVertex2i((LARGURA/3)*2,ALTURA-1);  glVertex2i((LARGURA/3)*2,1); glEnd();
	//HORIZONTAL
	glBegin(GL_LINES); glVertex2i(1,ALTURA/3);  glVertex2i(LARGURA-1,ALTURA/3); glEnd();
	glBegin(GL_LINES); glVertex2i(1,(ALTURA/3)*2);  glVertex2i(LARGURA-1,(ALTURA/3)*2); glEnd();

	//DESENHA OS X
	for(i=0; i < 9; i++){
		if(campoMarcado[i] == 1){
			desenhaX(cordenadasCamposJogada[i][0],cordenadasCamposJogada[i][1]); //passar cordenadas predefinidas em cordenadasCamposJogada
		}else if(campoMarcado[i] == -1){
			desenhaO(cordenadasCamposJogada[i][0],cordenadasCamposJogada[i][1]); //falta desenhar bola
		}
	}

	//verifica se houve vencedor e qual e o vencedor
	if(vencedor==0){
		verificaVencedor();
	}else{
	//DESENHA A LINHA EM CIMA DA SEQUENCIA DE 3 FORMADA
		glColor3f(0.0, 0.0, 1.0);
		glLineWidth(25.0);
		glBegin(GL_LINES);
			glVertex2f(cordenadasLinhasVencedor[marcaVencedor][0],cordenadasLinhasVencedor[marcaVencedor][1]);
			glVertex2f(cordenadasLinhasVencedor[marcaVencedor][2],cordenadasLinhasVencedor[marcaVencedor][3]);
		glEnd();
	}

	//  glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
 }

void keyboard(unsigned char key, int x, int y){
	switch (key) {
		case 27: //ESC=27 ENTER=13
			exit(0);
			break;
		case 'R':
		case 'r':
			resetarJogo();
			break;
		case 'P':
		case 'p':
			verPontos();
			break;
		case 'W':
		case 'w':
			printf("\n#########################################\n");
			for(i=0; i<9;i++){
				printf("[%i] - %i\n",i,campoMarcado[i]);
			}
			printf("\n#########################################\n");
			break;
	}
}

void mouse(int button, int state, int x, int y){
	
	if(button == GLUT_LEFT_BUTTON){
		if (state==GLUT_DOWN && vencedor == 0) 
		{  
			linha = descobreLinha(y); 
			coluna = descobreColuna(x);
			
			calc = coluna+(linha*3); //posicao no vetor de campos [0..9]
			if(campoMarcado[calc] == 0){ //Verifica se o campo esta livre
				if(VEZ==1){ //vez do X
					campoMarcado[calc] = VEZ; //marca o campo com X
					VEZ = -1; //passa a vez para o O
				}else if(VEZ==-1){ //vez do O
					campoMarcado[calc] = VEZ; //marca o campo com O
					VEZ = 1; //passa a vez para o X
				}
			}else{
				printf("Campo ja foi marcado!\n");
			} 
		} 
	}
}

void desenhaO(GLfloat x, GLfloat y) 
{ 
	glColor3f(1.0f, 0.0f, 0.0f); 
	GLfloat circle_points = 100.0f; 
	GLfloat angle;
	int raioX=7, raioY=7; 
	glLineWidth(3.0); 
	
	x = x + ((LARGURA/3)/2);
	y = y + ((ALTURA/3)/2);

	glBegin(GL_LINE_LOOP); 
	for (int i = 0; i < circle_points; i++) 
	{ 
		angle = 2*PI*i/circle_points; 
		glVertex2i((cos(angle)*raioX*10)+x, (sin(angle)*raioY*10)+y); 
	}
	glEnd();

}

void desenhaX(int x, int y){
	glColor3f(0.0f, 1.0f, 0.0f); 
	glLineWidth(5.0);

	//linhas cruzadas
	glBegin(GL_LINES); 
		glVertex2i( x , y ); glVertex2i( x + (LARGURA/3) , y + (ALTURA/3) );
		glVertex2i( x , y + (ALTURA/3) ); glVertex2i(x + (LARGURA/3) , y); 
	glEnd(); 
	//glFlush();
}

int descobreColuna(int x){

	if(x < LARGURA/3)//COL_1
		return 0;
	if(x > LARGURA/3 && x < (LARGURA/3)*2) //COL_2
		return 1;
	return 2; //COL_3

}

int descobreLinha(int y){

	if(y < ALTURA/3)//LINHA_1
		return 0;
	if(y > ALTURA/3 && y < (ALTURA/3)*2) //LINHA_2
		return 1;
	return 2; //LINHA_3

}

void resetarJogo(void){
	//limpa todos os campos colocando zero
	for(i = 0; i < 9; i++)
		campoMarcado[i] = 0;
	vencedor = 0;
	marcaVencedor = 0;
}

void showMenu(void){
	
	printf("\n*********************************************************************\n");
	printf("<<<<<<<<<<<<<	TRABALHO A2 COMPUTACAO GRAFICA	>>>>>>>>>>>>>\n");
	printf("*********************************************************************\n");
	printf("\n");
	printf("PRESSIONE  'R'   para Reiniciar Jogo\n");
	printf("PRESSIONE  'P'   para Mostrar Pontuacao\n");
	printf("PRESSIONE  'ESC' para Sair\n");
	printf("-------------------------------------------------------------------\n");
}

void verPontos(void){
	printf("\n## PONTUACAO : X[%i] x O[%i]\n",XVence,OVence);
}

void verificaVencedor(void){
	int t = 0;
	int j = 0;

	//verifica 3 casas iguais marcadas na mesma linha
	for(i=0;i<3;i++){//varia entre linhas
		t=0;
		for(j=0; j < 3; j++){
			t += campoMarcado[j+(i*3)];
		}
		//verifica se houve vencedor
		if((t == 3) || (t == -3)){
			vencedor = 1 * t;
			marcaVencedor = i + 3; //linha pra cortar
			printf("\n## VENCEDOR: Jogador[%i] Linha[%i]##\n",vencedor,i);

			//vencedor positivo X ganhou, negativo O ganhou
			if(vencedor > 0) XVence++;
			else OVence++;

			return;
		}
	}

	//verifica 3 casas iguais marcadas na mesma coluna
	for(i=0;i<3;i++){//varia entre colunas
		t=0;
		for(j=0; j < 3; j++){
			t += campoMarcado[i+(j*3)];
		}
		//verifica se houve vencedor
		if((t == 3) || (t == -3)){
			vencedor = 1 * t;
			marcaVencedor = i; //coluna pra cortar
			printf("\n## VENCEDOR: Jogador[%i] Coluna[%i]##\n",vencedor,i);

			//vencedor positivo X ganhou, negativo O ganhou
			if(vencedor > 0) XVence++;
			else OVence++;

			return;
		}
	}

	//verifica ganhador na transversal  [\]
	t = campoMarcado[0] + campoMarcado[4] +campoMarcado[8];
	//verifica se houve vencedor
	if((t == 3) || (t == -3)){
		vencedor = 1 * t;
		marcaVencedor = 6; //linha pra cortar
		printf("\n## VENCEDOR: Jogador[%i] Transversal[\\]##\n",vencedor,i);
		//vencedor positivo X ganhou, negativo O ganhou
		if(vencedor > 0) XVence++;
		else OVence++;
		return;
	}


	//verifica ganhador na transversal  [/]
	t = campoMarcado[2] + campoMarcado[4] + campoMarcado[6];
	//verifica se houve vencedor
	if((t == 3) || (t == -3)){
		vencedor = 1 * t;
		marcaVencedor = 7; //linha pra cortar
		printf("\n## VENCEDOR: Jogador[%i] transversal[/]##\n",vencedor,i);
		//vencedor positivo X ganhou, negativo O ganhou
		if(vencedor > 0) XVence++;
		else OVence++;
	}

}
