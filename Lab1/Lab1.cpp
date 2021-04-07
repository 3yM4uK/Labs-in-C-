#include <stdio.h>
#include <locale.h>
#include <Windows.h>

int abs(int);
int bitcount(int);
void to2(int);
void reverse(int*, int);

int main() {

	setlocale(LC_ALL, "Russian");
	int a, b, max;
	do 
	{
		printf("Введите первое значение интервала = ");
		if (scanf_s("%d", &a))
			break;
		else 
		{
			system("cls");
			rewind(stdin);
			printf("Incorrect input!\n");
		}
	}
	while (1);

	do
	{
		printf("Введите последнее значение интервала = ");
		if (scanf_s("%d", &b))
			break;
		else
		{
			system("cls");
			rewind(stdin);
			printf("Incorrect input!\n");
		}
	}
	while (1);
	if (a > b)
	{
		printf("Значение конца интервала меньше значения начала, поэтому они будут изменены местами.\n");
		int tmp = a; a = b; b = tmp;
	}

	max = a;

	for (int i = a; i <= b; i++)
		if (bitcount(abs(i)) > bitcount(abs(max)))
		{
			max = i;
		}

	printf("Число с максимальным количеством бит на интервале(2СС): ");
	to2(max);
	printf("\nЭто же число в 10СС: %d\n", max);
}

int abs(int value)
{
	if (value < 0)
		value *= -1;
	return value;
}

int bitcount(int value)
{
	int counter;
	for (counter = 0; value != 0; value >>= 1)
		if (value & 01)
			counter++;
	return counter;
}

void reverse(int* arr, int n)
{
	for (int i = 0; i < n / 2; i++)
	{
		int tmp = arr[i];
		arr[i] = arr[n - i - 1];
		arr[n - i - 1] = tmp;
	}
	for (int i = 0; i < n; i++)
		printf("%d", arr[i]);
}

void to2(int value)
{
	int counter = 0;
	int arr[20];
	int i = 0;

	if (value < 0)
	{
		putchar('-');
		value = abs(value);
	}

	while (value && i < 100) 
	{
		if (value & 01)
			arr[i] = 1;
		else
			arr[i] = 0;
		value >>= 1;
		counter++;
		i++;
	}

	reverse(arr, counter);
}
