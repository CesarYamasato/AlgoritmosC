#include <stdio.h>
#include <stdlib.h>
//nome: César Billalta Yamasato
//n° usp: 12542992
//valores intermediários
double a,b;
//input do usuário
double valor;
double precisao;
//loop
int i = 0;

int main(int argc, char *argv[]) {
	scanf("%lf", &valor); //input do valor que terá sua raiz quadrada calculada
	scanf("%lf", &precisao); //input da precisão e
	b = valor;
	a = b;
	
	while (valor - a*a > precisao || valor - a*a < -precisao)
	{
		if(!(valor > 0 && valor < 1))
		{
			b = b/2;
			if (valor > a*a)
			{
				a += b;
				printf("a %i: %g ; %g\n", i, a, b);
			}
			if (valor < a*a)
			{
				a -= b;
				printf("b %i: %g ; %g\n", i, a, b);
			}
		}
		else 
		{
			a += (valor- a*a);
			printf("c %i: %g\n", i, a);
		}
		//printf("d %i: %g\n", i, a);
		i++;
	}
	printf ("Numero de iteracoes: %i\n", i);
	printf("Diferenca absoluta: %.10f\n", (valor - a*a));
	printf ("Raiz quadrada: %.10f", a);
	return 0;
}
