#include <stdio.h>
#include <malloc.h>

void input(int** mt, int n, int m)
{
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < m; j++) 
        {
            printf("mt[%d][%d] = ", i, j);
            scanf_s("%d", &mt[i][j]);
        }
    }

    putchar('\n');
}

void output(int** mt, int n, int m)
{
    for (int i = 0; i < n; i++, putchar('\n')) 
    {
        for (int j = 0; j < m; j++)
        {
            printf("%3d", mt[i][j]);
        }
    }

    putchar('\n');
}

size_t getNextStrIndexToMaxEl(int** mt, int n, int m)
{
    int max = 0;
    size_t strIndex = 0;
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < m; j++)
        {
            if (mt[i][j] > max)
            {
                max = mt[i][j];
                strIndex = i;
            }
        }
    }

    return strIndex + 1;
}
void copyArray(int* firstArr, int* secondArr, int arrsize) 
{
    for (int i = 0; i < arrsize; i++)
    {
        secondArr[i] = firstArr[i];
    }
}
void freeMt(int**& mt, int n) 
{
    for (int i = 0; i < n; i++)
    {
        free(mt[i]);
    }
    free(mt);
}

int** nullElements(int**& mt, int m, int n, int index)
{
    int** newMatrix;
    if (!(newMatrix = (int**)calloc(m * n, sizeof(int*))))
        return 0;
    for (int i = 0; i < n; i++)
    {
        if (!(newMatrix[i] = (int*)calloc(n, sizeof(int))))
            return 0;
    }
    for (int i = 0, j = 0; i < n && j < m; i++, j++)
    {
        if (i == index)
            copyArray(mt[i], newMatrix[j + 1], n);
        else
        {
            copyArray(mt[i], newMatrix[j], n);
        }
    }

    freeMt(mt, m);
    return newMatrix;
}

void reflectSide(int** mt, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            int tmp = mt[i][j];
            mt[i][j] = mt[n - j - 1][n - i - 1];
            mt[n - j - 1][n - i - 1] = tmp;
        }
    }
}

void reflectMain(int** mt, int n) 
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            int tmp = mt[j][i];
            mt[j][i] = mt[i][j];
            mt[i][j] = tmp;
        }
    }
}

int main()
{
    int** mt;
    int** newArr;
    int n;

    printf("n = ");
    scanf_s("%d", &n);

    int m = n - 1;
    if (!(mt = (int**)malloc(n * (n - 1) * sizeof(int))))
        return 0;

    for (int i = 0; i < n; i++)
    {
        if (!(mt[i] = (int*)malloc(n * sizeof(int))))

            return 0;
    }

    input(mt, m, n);
    output(mt, m, n);
    int id = getNextStrIndexToMaxEl(mt, n - 1, n);
    mt = nullElements(mt, m, n, id);

    printf("Matrix with a string of zeros added: \n");
    output(mt, n, n);
    printf("The matrix reflected along the main diagonal:\n");
    reflectMain(mt, n);
    output(mt, n, n);
    printf("The matrix reflected along the side diagonal:\n");
    reflectSide(mt, n);
    output(mt, n, n);
    freeMt(mt, n);
}