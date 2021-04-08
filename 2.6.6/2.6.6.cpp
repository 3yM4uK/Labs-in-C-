#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int compare(double x, double accuracy, double* resultRight);
int fact(int number);


int main()
{
    printf("Enter x and accuracy ");

    const double zero = 0.0;
    double x, accuracy, resultRight = 0;
    scanf_s("%lf %lf", &x, &accuracy);
    int result = compare(x, accuracy, &resultRight);

    printf("Result is %d \nSin(x) = %lf \nRightPart is %lf\n", result, sin(x), resultRight);

    system("pause");
    return 0;
}   

int compare(double x, double accuracy, double* resultRight)
{
    int n = 1;
    double bufferSin = sin(x);
    if (bufferSin >= 0)
    {
        do
        {
            if (n % 2 == 0)
            {
                *resultRight -= pow(x, 2 * n - 1) / (double)fact(2 * n - 1);
            }
            else
            {
                *resultRight += pow(x, 2 * n - 1) / (double)fact(2 * n - 1);
            }
            n++;

        } while (fabs(bufferSin - *resultRight) > accuracy);
        return --n;
    }
    else
    {
        return -1;
    }
}

int fact(int number)
{
    if (number == 0 || number == 1)
    {
        return 1;
    }
    else
    {
        return (number--) * fact(number);
    }
}