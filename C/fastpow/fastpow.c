#include<stdio.h>
int i;
int n;
fastpow(int i, int n)
{
    if(i != 1)
    {
        if(i%2) return fastpow(i/2,n)*fastpow(i/2,n)*n;
        return fastpow(i/2,n)*fastpow(i/2,n);
    }
    return n;
}

int main()
{
    scanf("%i",&n);
    scanf("%i",&i);
    printf("%i",fastpow(i, n));
    return 0;
}
