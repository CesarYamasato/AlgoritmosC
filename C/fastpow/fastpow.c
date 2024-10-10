#include<stdio.h>
int i;
int n;
fastpow(int i, int n)
{
    if(i != 1)
    {
        int exponent = fastpow(i/2,n);
        if(i%2) return exponent*exponent*n;
        return exponent*exponent;
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
