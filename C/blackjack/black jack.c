#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int i, a, o, p;
int mao [4][12];
int sacar;
int cont = 1;
int continuar;
int soma;

int main(int argc, char *argv[])
 {
	srand(time(NULL));
	
	for (o = 0; o < 4; o++)
	{
		for (p = 0; p < 12; p++)
		{
			mao[o][p] = 0;
		}
	}
	
	while (cont)
	{	
		continuar = 1;
		printf("sua mao e: \n");
		while (continuar)
		{
			sacar = 1;
			while (sacar)
			{
				a = rand() % (12);
				i = rand() % (4);
				if (!mao [i][a])
				{
					mao[i][a] = 1;
					sacar = 0;
					soma = soma+a+1;
				//	printf ("%i\n%i\n", i,a);
				}
			}
			for (o = 0; o <4; o++)
			{
				for (p = 0; p <12; p++)
				{
					if (mao[o][p])
					{ 
						printf ("%i%c \n", p+1, o+3);
					}
				}
			}
		
			continuar = 0;
		}
		printf("pegar outra carta? (s =1/n =0) \n");
	
		if (soma < 21)
		{
		 if (!scanf("%i", &cont)){
		 	cont = 1;
		 	fflush(stdin);
		 	printf("ssssss");
		 }
		}
		else
		{
			cont = 0;
		}
		
	}
	printf ("voce atingiu %i pontos acima de 21\n", soma - 21);
	system("pause");
	return 0;
}
