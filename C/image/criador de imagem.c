//César Billalta Yamasato n°usp: 12542992
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// constante que define o valor maximo que um pixel pode assumir.

#define VALOR_MAXIMO 255

// constantes que definem as strings que podem ser especificadas na entrada, cada uma associada uma operacao.

#define RETA "RETA"
#define RETANGULO_CONTORNO "RETANGULO_CONTORNO"
#define RETANGULO_PREENCHIDO "RETANGULO_PREENCHIDO"
#define CLONA "CLONA"
#define CLONA_INV "CLONA_INV"
#define CLONA_HOR "CLONA_HOR"
#define CLONA_VER "CLONA_VER"
#define FIM "FIM"

int b= 0;
typedef struct {

	int altura;	// altura da imagem (numero de linhas)
	int largura;   	// largura da imagem (numero de colunas na imagem)
	int ** matriz;  // ponteiro para a matriz que armazena o conteudo da imagem

} Imagem; // estrutura que representa uma imagem.

typedef struct {

	int x; // coordenada horizontal
	int y; // coordenada vertical

} Ponto2D; // estrutura que representa um Ponto no plano 2D.


// funcao que cria uma imagem vazia e a devolve. Precisar ser completada para funcionar corretamente.
Imagem * cria_imagem(int largura, int altura){
	int i;
	int j;
	
	Imagem * imagem = (Imagem *) malloc(sizeof(Imagem));

	imagem->altura = altura;	// isto está correto?
	imagem->largura = largura;	// e isto?
	
	imagem->matriz = (int **) malloc(altura * sizeof(int *));
	
	for (i= 0; i < altura; i++)
	{
		imagem -> matriz[i] = (int *) malloc (sizeof(int) * largura);
	}
	for(i= 0; i < altura; i++)
	{
		for (j = 0; j <largura; j++){
			imagem->matriz[i][j] = 0;
		}
	}

	return imagem;
}

// funcao (ja completa) que libera os recursos de memoria associados a uma imagem.

void libera_imagem(Imagem * imagem){

	int lin;

	for(lin = 0; lin < imagem->altura; lin++) free(imagem->matriz[lin]); // liberacao de cada linha da matriz (cada linha é um vetor de int)

	free(imagem->matriz);	// liberacao da matriz (que é na realidade um vetor de linhas, ou um vetor de "vetor de int")
	free(imagem);		// liberacao da estrutura em si
}


// funcao (ja completa) que salva uma imagem em um arquivo, no formato PGM. Programas/utilitarios que trabalham
// com imagens bitmap (como o Gimp e visualizadores de imagens normalmente instalados em ambiente Linux) em geral
// reconhecem formato. Se tiver dificuldades para visualizar os arquivos de imagem salvos por esta funcao, um visualizador 
// online pode ser encontrado neste link: http://paulcuth.me.uk/netpbm-viewer/.

void salva(Imagem * imagem, char * nomeArquivo){

	int lin, col;
	FILE * saida = fopen(nomeArquivo, "w"); // abertura do arquivo para escrita ("w" - write)

	if(saida){

		// o 'fprintf' funciona de forma igual ao 'printf', com a diferença que 
		// o conteudo eh escrito em um arquivo (associado a variavel 'saida')
	
		fprintf(saida, "P2\n%d %d\n%d\n", imagem->largura, imagem->altura, VALOR_MAXIMO);

		
		for(lin = 0; lin < imagem->altura; lin++){

			for(col = 0; col < imagem->largura; col++){

				fprintf(saida, (col == 0 ? "%d" : " %d"), imagem->matriz[lin][col]);  				
			}
			
			fprintf(saida, "\n");
		}
	}

	fclose(saida); // fechamento do arquivo
}


void reta(Imagem * imagem, Ponto2D p1, Ponto2D p2, int cor)
{
	//printf("\n%i,%i\n%i,%i\n", p1.x,p1.y,p2.x,p2.y);
	int i;
	int j;
	
	int x;
	int y;
	x = (p1.x < p2.x)? p1.x: p2.x;
	y = (p1.y < p2.y)? p1.y: p2.y; 
	
	float m;
	int div_zero;
	m = (p1.x == p2.x) ? 0 : ((float)p1.y - p2.y)/(float)(p1.x - p2.x);  //caso p1.x seja igual a p2.x, haveria divisão por 0, então eu fiz isso para evitar o fim forçado da execução do programa
	div_zero = (p1.x == p2.x) ? 0 : 1;
	
	for (i = y; i <= y + abs(p1.y-p2.y); i++)
	{
		if (div_zero)
		{
			for (j = x; j <= x + abs(p1.x-p2.x); j++)
			{
				if(i <= m*(j - p1.x) + 0.5 + p1.y  && i >= m*(j - p1.x) + p1.y - 0.5) //baseando-me na equação da reta y = m*(x - x0) + y0, aqui eu fiz com que qualquer ponto dentro de determinada precisão fosse "pintado"
				{
					//printf("%f\n", m*(j - p1.x) + p1.y); -> usado para debug
					//printf("%i , %i\n", i,j); -> usado para debug
					imagem->matriz[i][j] = cor;
					
				}
			}
		}
		else
		{
			//printf("%i : ",i); -> usado para debug
			//printf("%i\n", p1.x); -> usado para debug
			imagem->matriz[i][p1.x] = cor;
		
		}
	}	
}


void retangulo_contorno(Imagem * imagem, Ponto2D p1, Ponto2D p2, int cor){
	Ponto2D p3;
	p3.x = p1.x;
	p3.y = p2.y;
	
	Ponto2D p4;
	p4.y = p1.y;
	p4.x = p2.x;
	
	reta(imagem, p1,p3,cor);
	reta(imagem, p1,p4,cor);
	reta(imagem, p2,p3,cor);
	reta(imagem, p2,p4,cor);	
}


void retangulo_preenchido(Imagem * imagem, Ponto2D p1, Ponto2D p2, int cor) //esta função era inicialmente muito ineficiente em termos de memória e tempo de execução
{ 																			//porque eu havia utilizado a função da reta dentro de um for loop para gerar várias retas até formar o retângulo1
	int i;
	int j;
	int x;
	int y;
	
	x = (p1.x < p2.x)? p1.x: p2.x;
	y = (p1.y < p2.y)? p1.y: p2.y; 
	/*
	Ponto2D p3; 															
	p3.x = (p1.x < p2.x)?p1.x: p2.x; 
	p3.y = p2.y;
	
	Ponto2D p4; 
	p4.x = p3.x;
	p4.y = p1.y;*/
	
	for (i = y; i < y + abs (p1.y - p2.y); i++)
	{
		for(j = x; j < x + abs(p2.x - p1.x); j++)
		{
			/*reta(imagem,p3,p4,cor);
			p3.x++;
			p4.x++;*/
			imagem -> matriz [i][j] = cor;
		}
	}
	
}


void clona(Imagem * imagem, Ponto2D p1, Ponto2D p2, Ponto2D p3)
{
	int i;
	int j;
	
	int x;
	int y;
	
	x = (p1.x < p2.x)? p1.x : p2.x;
	y = (p1.y < p2.y)? p1.y : p2.y;	
	
	for(i = 0; i <= abs(p1.y - p2.y); i++)
	{
		for(j = 0; j <= abs(p1.x - p2.x); j++)
		{
		//	printf("%i : %i\n\n", p3.x + i,p3.x +j); -> usado para debug
		//	printf("%i : %i\n\n", i+y,j+x); -> usado para debug
			imagem->matriz[p3.y + i][p3.x + j] = imagem -> matriz[i+y][j+x];
		}
	}
}


void clona_inverte_cor(Imagem * imagem, Ponto2D p1, Ponto2D p2, Ponto2D p3){

	int i = 0;
	int j = 0;
	
	int x = 0;
	int y = 0;
	
	x = (p1.x < p2.x)? p1.x : p2.x;
	y = (p1.y < p2.y)? p1.y : p2.y;	
	
	for(i = 0; i <= abs(p1.y - p2.y); i++)
	{
		for(j = 0; j <= abs(p1.x - p2.x); j++)
		{
			//printf("%i : %i\n\n", p3.x + i,p3.x +j); -> usado para debug
			//	printf("%i : %i\n\n", i+y,j+x); -> usado para debug
			imagem->matriz[p3.y + i][p3.x + j] = VALOR_MAXIMO - imagem -> matriz[i+y][j+x];
		}
	}
}


void clona_espelha_horizontal(Imagem * imagem, Ponto2D p1, Ponto2D p2, Ponto2D p3){
	int i = 0;
	int j = 0;
	
	int x = 0;
	int y = 0;
	
	x = (p1.x < p2.x)? p1.x : p2.x;
	y = (p1.y < p2.y)? p1.y : p2.y;	
	
	for(i = abs(p1.y - p2.y); i >= 0 ; i--)
	{
		for(j = abs(p1.x - p2.x); j >= 0; j--)
		{
			//printf("%i : %i == %i : %i \n", p3.y + i, p3.x +j, i , p2.x - j); -> usado para debug
			imagem->matriz[p3.y + i][p3.x + j] = imagem -> matriz[p1.y + i][p2.x - j];
		}
	}
}


void clona_espelha_vertical(Imagem * imagem, Ponto2D p1, Ponto2D p2, Ponto2D p3){

	int i = 0;
	int j = 0;
	
	int x = 0;
	int y = 0;
	
	x = (p1.x < p2.x)? p1.x : p2.x;
	y = (p1.y < p2.y)? p1.y : p2.y;	
	printf("%i", y);
	for(i = abs(p1.y - p2.y); i >= 0 ; i--)
	{
		for(j = abs(p1.x - p2.x); j >= 0; j--)
		{
			imagem->matriz[p3.y + i][p3.x + j] = imagem -> matriz[p2.y - i][p1.x + j];
		}
	}
}


int main(){
	//FILE * input = fopen ("testes.txt", "r"); -> eu estava usando um arquivo de texto com as instruções para fazer os testes e comparar as strings

	int largura, altura;
	char operacao[32], nome_arquivo[256];
	Imagem * img;

	scanf( "%s %d %d", nome_arquivo, &largura, &altura);
	img = cria_imagem(largura, altura);

	while(scanf(  "%s", operacao) == 1 && strcmp(operacao, FIM) != 0)
	{
	
		if(strcmp(operacao, RETA) == 0){
			Ponto2D p1;
			Ponto2D p2;
			int cor;

			scanf( "%i", &p1.x);
			scanf( "%i", &p1.y);
			scanf( "%i", &p2.x);
			scanf( "%i", &p2.y);
			scanf( "%i", &cor);
			reta(img, p1, p2, cor);
		}
		else if(strcmp(operacao, RETANGULO_CONTORNO) == 0){
			Ponto2D p1;
			Ponto2D p2;
			int cor;

			scanf( "%i", &p1.x);
			scanf( "%i", &p1.y);
			scanf( "%i", &p2.x);
			scanf( "%i", &p2.y);
			scanf( "%i", &cor);
			retangulo_contorno(img, p1, p2, cor);
		}
		else if(strcmp(operacao, RETANGULO_PREENCHIDO) == 0){
			Ponto2D p1;
			Ponto2D p2;
			int cor;

			scanf( "%i", &p1.x);
			scanf( "%i", &p1.y);
			scanf( "%i", &p2.x);
			scanf( "%i", &p2.y);
			scanf( "%i", &cor);
			retangulo_preenchido(img, p1, p2, cor);
		}
		else if(strcmp(operacao, CLONA) == 0){
			Ponto2D p1;
			Ponto2D p2;
			Ponto2D p3;
			int cor;

			scanf( "%i", &p1.x);
			scanf( "%i", &p1.y);
			scanf( "%i", &p2.x);
			scanf( "%i", &p2.y);
			scanf( "%i", &p3.x);
			scanf( "%i", &p3.y);
			clona(img, p1, p2, p3);
		}
		else if(strcmp(operacao, CLONA_INV) == 0){
			Ponto2D p1;
			Ponto2D p2;
			Ponto2D p3;
			int cor;

			scanf( "%i", &p1.x);
			scanf( "%i", &p1.y);
			scanf( "%i", &p2.x);
			scanf( "%i", &p2.y);
			scanf( "%i", &p3.x);
			scanf( "%i", &p3.y);
			clona_inverte_cor(img, p1, p2, p3);
		}
		else if(strcmp(operacao, CLONA_HOR) == 0){
			Ponto2D p1;
			Ponto2D p2;
			Ponto2D p3;
			int cor;

			scanf( "%i", &p1.x);
			scanf( "%i", &p1.y);
			scanf( "%i", &p2.x);
			scanf( "%i", &p2.y);
			scanf( "%i", &p3.x);
			scanf( "%i", &p3.y);
			clona_espelha_horizontal(img, p1, p2, p3);
		}
		else if(strcmp(operacao, CLONA_VER) == 0){
			Ponto2D p1;
			Ponto2D p2;
			Ponto2D p3;
			int cor;
			
			scanf( "%i", &p1.x);
			scanf( "%i", &p1.y);
			scanf( "%i", &p2.x);
			scanf( "%i", &p2.y);
			scanf( "%i", &p3.x);
			scanf( "%i", &p3.y);
			clona_espelha_vertical(img, p1, p2, p3);
		}
	}

	salva(img, nome_arquivo);
	libera_imagem(img);

	return 0;	
}
