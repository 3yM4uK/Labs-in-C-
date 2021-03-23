#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include <locale.h>
#include <iostream>

using namespace std;

void menu();
int inputInt();
int function1();
int function2();
int function3();
int function4();

void function5(int cement, int graviu, int beton, int country);
void function6(int cement, int graviu, int beton, int country);

void menu()
{
	int temp, cement = 0, graviu = 0, beton = 0, country = 0;

	while (1)
	{

		printf("1. Заказ на цемент\n");
		printf("2. Заказ на гравий\n");
		printf("3. Заказ на бетон\n");
		printf("4. Выбор страны доставки (Беларусь/Россия/Украина/Молдавия\n");
		printf("5. Общие сведения \n");
		printf("6. Решение по ващему заказу \n");
		printf("7. Создатель \n");
		printf("8. Выйти \n");

		temp = inputInt();

		if (temp < 1 || temp > 8)
			printf(" Вы ввели неверные данные\n");
		else
		{

				switch (temp)
				{
				case 1:
					system("cls");
					cement = function1();
					system("cls");
					break;
				case 2:
					system("cls");
					graviu = function2();
					system("cls");
					break;
				case 3:
					system("cls");
					beton = function3();
					system("cls");
					break;
				case 4:
					system("cls");
					country = function4();
					system("cls");
					break;
				case 5:
					system("cls");
					function5(cement, graviu, beton, country);
					system("pause");
					system("cls");
					break;
				case 6:
					system("cls");
					function6(cement, graviu, beton, country);
					system("pause");
					system("cls");
					break;
				case 7:
					system("cls");
					printf("Шитик Дмитрий(КСИС, ИИТП, 053503).\nVersoin 1.0\n");
					system("pause");
					system("cls");
					break;
				case 8: 
					system("cls");
					return;
					break;
				}

			}
		}


}

int function1()
{
	int cement;
	printf("Сколько тонн цемента Вы хотите заказать? (Ответ дать ввиде цифры)\n");

	while (1)
	{
		cement = inputInt();
		if (cement < 0 || cement > 1000000)
			printf(" Вы ввели неверные данные. Повторите поптыку\n");
		else
			break;
	}

	return cement;
}

int function2()
{
	int graviu;
	printf("Сколько тонн гравия Вы хотите заказать? (Ответ дать ввиде цифры)\n");
	
	while (1)
	{
		graviu = inputInt();
		if (graviu < 0 || graviu > 1000000)
			printf(" Вы ввели неверные данные. Повторите поптыку\n");
		else
			break;
	}

	return  graviu;

}


int function3()
{
	int beton;
	printf("Сколько тонн бетона Вы хотите заказать? (Ответ дать ввиде цифры)\n");
	
	while (1)
	{
		beton = inputInt();
		if (beton < 0 || beton > 1000000)
			printf(" Вы ввели неверные данные. Повторите поптыку\n");
		else
			break;
	}

	return  beton;

}


int function4()
{
	int country;
	printf("Выбор страны доставки: (1-Беларусь, 2-Россия, 3-Украина, 4-Молдавия)\n");
	

	while (1)
	{
		country = inputInt();

		if (country <= 0 || country >= 5)
			printf(" Вы ввели неверные данные. Повторите поптыку\n");
		else
			break;
	}

	return  country;

}


void function5(int cement, int graviu, int beton, int country)
{
	printf("Стоимость цемента, гравия, бетона за тонну.(230$/142$/260$)\n");
	printf(" Вы заказали цемеента на сумму: ");
	printf("%d\n", cement * 230);
	printf(" Вы заказали гравия на сумму: ");
	printf("%d\n", graviu * 142);
	printf(" Вы заказали бетона на сумму: ");
	printf("%d\n", beton * 260);

	int vagon = cement + graviu + beton;
	if (vagon == 0)
	{
		printf(" Количество вагонов: 0");
		vagon = 0;
	}
	else
	{
		printf("Количество вагонов: %d\n", (vagon / 50) + 1);
		vagon = (vagon / 50)	 + 1;
	}
	
	if (country == 1)
		printf(" Стоимость перевозки в Беларусь: %d\n", vagon * 200);
	else if (country == 2)
		printf(" Стоимость перевозки в Росиию: %d\n", vagon * 320);
	else if (country == 3)
		printf(" Стоимость перевозки в Украину: %d\n", vagon * 320);
	else if (country == 3)
		printf(" Стоимость перевозки в Молдавию: %d\n", vagon * 360);
	else
	{
		printf(" Вы не указали страну перевозки. Вернитесь назад и укажите, куда необходимо доставить груз ");
	}

}

void function6(int cement, int graviu, int beton, int country)
{	
	int cash = ((cement * 230) + (graviu * 142) + (beton * 260)) - ((cement * 160) + (graviu * 96) + (beton * 205));
	
	int vagon = cement + graviu + beton;

	if (vagon == 0)
		vagon = 0;
	else
		vagon = (vagon / 50) + 1;

	if (country == 1)
		cash = cash - (vagon * 200);
	else if (country == 2)
		cash = cash - (vagon * 320);
	else if (country == 3)
		cash = cash - (vagon * 320);
	else if (country == 3)
		cash = cash - (vagon * 360);
	else
		cash = 0;


	if (cash < 25000)
	{
		printf(" Сумма заказанного груза не удолетворяет треблваниям компании.\n Заказ должен быть от 25к$ чистой прибыли для нас\n");
	}
	else
		printf(" Ваш заказ одобрен \n");
	
}

int inputInt()
{
	int i = 0, result = 0;
	char str[255];
	fgets(str, 255, stdin);
	if (str[0] == '0')
	{
		return -1;
	}
	while (str[i] != '\n' && str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			result *= 10;
			result += (str[i] - '0');
			i++;
		}
		else
			return-1;
	}
	return result;
}



int main()
{
	char* locale = setlocale(LC_ALL, "");
	menu();
	system("pause");
	return 0;

}