#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//Nome: César Billalta Yamasato
//Número USP: 12542992
float a[3];
float triang[3];
//arrays usados para os lados do triângulo
int i,k,o;
int u,r;
//variáveis usadas para for loops
int lad_ig;
float x;
float y;
//"parâmetros" do triângulo

int main(int argc, char *argv[]) {
	//printf ("insira os valores dos lados do triangulo\n"); 
	//input dos dados
	for (i = 0; i < 3; i++)
	{
		scanf("%f", &a[i]);
	}
	//esse é um algoritmo que eu fiz que organiza um array em orgem crescente, gostaria de saber se há uma maneira mais eficiente de escrever
	for (i = 0; i < 3; i++)
	{
		u = 0;
		r = 0;
		for (k = 0; k < 3; k++)
		{
			if (a[i] > a[k])
			{
				u++;
			}
			else{
				if (a[i] == a[k])
				{
					r++;
					lad_ig++;
				}
			}
		}
		triang[u] = a[i];
		for (o = 0; o < r; o++)
			{
				triang[u+o] = a[i];
			}
	}
	
	if(triang[0] + triang[1] > triang[2]) //checa se o triângulo é válido
	{
		printf("Medidas dos lados formam um triangulo VALIDO\n");
		
		//tem um jeito mais fácil de checar qual tipo de triângulo é ("automatizado")? 
		if (lad_ig == 3){
			printf("Classificacao em funcao dos lados: ESCALENO\n");
		}
		else if (lad_ig == 9){
			printf("Classificacao em funcao dos lados: EQUILATERO\n");
		}
		else {
			printf("Classificacao em funcao dos lados: ISOSCELES\n");
		}
		
		//atribui o balor da altura e largura baseado no tipo de triângulo
		if((triang[1]*triang[1] + triang[0]*a[0]) < (triang[2]*triang[2])){
			x = (triang[2]*triang[2] - triang[1]*triang[1] - triang[0]*triang[0])/(2*triang[0]);
			y = sqrt(triang[1]*triang[1] - x*x);
			printf ("Classificacao em funcao dos angulos: OBTUSO\n");
		}
		else if ((triang[1]*triang[1] + triang[0]*a[0]) > (triang[2]*triang[2])){
			x = (triang[2]*triang[2] - triang[1]*triang[1] - triang[0]*triang[0])/(-2*triang[0]);
			y = sqrt(triang[1]*triang[1] - x*x);
			printf ("Classificacao em funcao dos angulos: AGUDO\n");
		}
		else {
			x = a[0];
			y = a[1];
			printf ("Classificacao em funcao dos angulos: RETO\n");
		}
		float area = (triang[0]*y)/2;
		printf("Area do triangulo: %g\n", area);
	}
	else {
		printf("Medidas dos lados formam um triangulo INVALIDO\n");
	}
	return 0;
}
