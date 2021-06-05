#include <stdio.h>
#include <math.h>
#include <locale.h>
#include "laba_2_2.h"

int fact(int n)
{
    int f = 1;
    int i;
    for (i = 1; i <= n; i++)
        f = f * i;
    return f;
}

int sum(float x, float e)
{
	int n = 0;
	float sum = 0;
	while(fabs(sin(x) - sum) >= e)
	{
		n++;
		sum += pow(-1, n - 1)*pow(x, 2 * n - 1) / fact(2 * n - 1);
	}
	return n;
}

int main() 
{
	setlocale(LC_ALL, "Rus");
	float x, e;
	int n=0;
	while (n==0) 
	{
		printf("Введите значение х(оно должно быть от -pi/2 до pi/2):\n");
		scanf("%f", &x);
		if (x <= acos(-1) / 2 || x >= -acos(-1) / 2)
		break;
	}
	while (n==0)
	{
		printf("Введите значение е\n");
		if (scanf("%f", &e) != 1)
			printf("Введите значение е: ");
		else
		break;
	}
	printf("sin = %f, e = %f, n = %d",sin(x), e, sum(x, e));
	return 0;
}