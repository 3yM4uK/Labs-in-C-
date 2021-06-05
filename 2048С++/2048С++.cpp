#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <time.h>
#include <string.h>

#define SIZE 4
#define WAIT_ANY_KEY getchar()


bool printEndScreen(int matrix[SIZE][SIZE], char name_player[9], int score, int max);
bool printScreen(int matrix[SIZE][SIZE], int, char name_player[9]);
bool shiftElementsUp(int matrix[SIZE][SIZE], int* score);
bool turnElementsRight(int matrix[SIZE][SIZE], int);
bool addRandomElement(int matrix[SIZE][SIZE]);
bool verificationEndGame(int matrix[SIZE][SIZE]);
char* gameNumber(int, char numх[5]);
int maxNumber(int matrix[SIZE][SIZE]);
int gen_random(int, int);


int main() {

Start:

	bool processing = true;				// Состояние работы
	bool result;						//Результат выполнения действия
	bool no_char;						//Флаг вводимого значения
	char name_player[9];				//Строка с именем игрока
	char ch[2];							//ВВодимый знак
	char c;								//Зажатая клавиша
	int max;							//Максимальное значение
	int score = 0;						//Очки игрока

	int matrix[SIZE][SIZE] = {			
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0}
	};

	system("cls");										
	srand((unsigned int)time(NULL));					

	//Подготовка запуска игры
	addRandomElement(matrix);
	addRandomElement(matrix);

	printScreen(matrix, score, name_player);


	do {
		//Сброс результатов после одного цикла
		result = false;
		no_char = false;

		//Получение зажатой клавиши
		c = _getch();


		switch (c) {

			//При сдвиге вверх
		case 'W': case 'w':
			result = shiftElementsUp(matrix, &score);
			break;

			//При сдвиге вниз
		case 'S': case 's':
			turnElementsRight(matrix, 2);
			result = shiftElementsUp(matrix, &score);
			turnElementsRight(matrix, 2);
			break;

			//При сдвиге влево
		case 'A': case 'a':
			turnElementsRight(matrix, 1);
			result = shiftElementsUp(matrix, &score);
			turnElementsRight(matrix, 3);
			break;

			//При сдвиге вправо
		case 'D': case 'd':
			turnElementsRight(matrix, 3);
			result = shiftElementsUp(matrix, &score);
			turnElementsRight(matrix, 1);
			break;

			//При нажатии выхода
		case 'B': case 'b':
			result = false;
			processing = false;
			break;

			//Если не совершенно никакое действие
		default:
			no_char = true;
		}

		//Проверка конца игры
		max = maxNumber(matrix);											
		if (max == 11)
			processing = false;												
		else if (result && !no_char) {										
			addRandomElement(matrix);										
			printScreen(matrix, score, name_player);						
		}
		else if (!result) if (!verificationEndGame(matrix))				
			processing = false;

	} while (processing);

	//Конец игры
	printEndScreen(matrix, name_player, score, max);
	scanf("%1s", &ch);
	if (ch[0] == 'Y' || ch[0] == 'y') goto Start;


	WAIT_ANY_KEY;
	return 0;
}


//Добавление на поле рандомный элемент в рандомную пустую ячейку

bool addRandomElement(int matrix[SIZE][SIZE]) {

	bool success = false;					//Успешность завершения действия
	bool processing = false;				//Процесс добавления
	int X, Y;							//Координаты добавляемого элемента

	if (!matrix) return false;

	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			if (matrix[i][j] == 0) processing = true;

	//Добавление рандомного элемента
	while (processing && !success) {					
		X = gen_random(0, 3);
		Y = gen_random(0, 3);
		//Проверка что в данных координатах точно есть свободное окно
		if (matrix[Y][X] == 0) {
			matrix[Y][X] = gen_random(1, 2);				
			success = true;
		}
	}

	return success;
}

///Генерация рандомного числа в диапазоне
int gen_random(int range_min, int range_max) {
	return range_min + rand() % (range_max - range_min + 1);
}

/// Выполнить игровой сдвиг вверх

bool shiftElementsUp(int matrix[SIZE][SIZE], int* score) {

	bool success = false;															//Успешность изменений

	if (!matrix) return false;

	/// Сдвиг вверх перед склеиванием 
	for (int i = 0; i < SIZE; i++)														
		for (int j = 0; j < SIZE - 1; j++)												

			if (matrix[j][i] == 0)												
				for (int k = j + 1; k < SIZE; k++) if (matrix[k][i] != 0)			 
				{	
					matrix[j][i] = matrix[k][i];
					matrix[k][i] = 0;
					success = true;
					break;
				}
	//Склеивание
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE - 1; j++)
			if (matrix[j][i] == matrix[j + 1][i] && matrix[j][i] != NULL) {				
				*score += matrix[j][i] * 10;												
				matrix[j][i]++;
				matrix[j + 1][i] = 0;
				success = true;
			}

	///Повторный сдвиг, после склеивания  
	for (int i = 0; i < SIZE; i++)														
		for (int j = 0; j < SIZE - 1; j++)										
			if (matrix[j][i] == 0)													
				for (int k = j + 1; k < SIZE; k++) if (matrix[k][i] != 0)					
				{	
					matrix[j][i] = matrix[k][i];
					matrix[k][i] = 0;
					success = true;
					break;
				}

	return success;

}

/// Поворот матрици n раз

bool turnElementsRight(int matrix[SIZE][SIZE], int count) {

	bool success = false;											//Успешность переворота
	int buffer;		
	//Буфер значения
	if (!matrix) return false;

	/// Поворот матрицы на COUNT раз, по часовой стрелке 
	for (int k = 0; k < count; k++)								
		for (int i = 0; i < SIZE / 2 && matrix != NULL; i++)		
			for (int j = i; j < SIZE - 1 - i; j++)			
			{
				buffer = matrix[i][j];
				matrix[i][j] = matrix[SIZE - j - 1][i];
				matrix[SIZE - j - 1][i] = matrix[SIZE - i - 1][SIZE - j - 1];
				matrix[SIZE - i - 1][SIZE - j - 1] = matrix[j][SIZE - i - 1];
				matrix[j][SIZE - i - 1] = buffer;
				success = true;
			}

	return success;

}

/// Поиск максимального значения игрового поля
int maxNumber(int matrix[SIZE][SIZE]) {

	if (!matrix) return false;

	int maxNumber = 0;

	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			if (maxNumber < matrix[i][j]) maxNumber = matrix[i][j];

	return maxNumber;
}

/// Отпечатать экран игры
bool printScreen(int matrix[SIZE][SIZE], int score, char name_player[9]) {

	char num[16][5];													//Переменная для отображения числа ячейки
	system("cls");														//Очищение окна консоли

	if (!matrix) return false;
	/// Экран
	printf("_____________________________________\n");
	printf("|             GAME 2048             |\n");
	printf("|        Score:%7d              |\n", score);
	printf("|___________________________________|\n");
	printf("|        |        |        |        |\n");
	//1-я строка игрового поля
	printf("|  %4s  |  %4s  |  %4s  |  %4s  |\n",
		gameNumber(matrix[0][0], num[0]), gameNumber(matrix[0][1], num[1]),
		gameNumber(matrix[0][2], num[2]), gameNumber(matrix[0][3], num[3]));
	//2-я строка игрового поля
	printf("|        |        |        |        |\n");
	printf("|________|________|________|________|\n");
	printf("|        |        |        |        |\n");
	printf("|  %4s  |  %4s  |  %4s  |  %4s  |\n",
		gameNumber(matrix[1][0], num[4]), gameNumber(matrix[1][1], num[5]),
		gameNumber(matrix[1][2], num[6]), gameNumber(matrix[1][3], num[7]));
	//3-я строка игрового поля
	printf("|        |        |        |        |\n");
	printf("|________|________|________|________|\n");
	printf("|        |        |        |        |\n");
	printf("|  %4s  |  %4s  |  %4s  |  %4s  |\n",
		gameNumber(matrix[2][0], num[8]), gameNumber(matrix[2][1], num[9]),
		gameNumber(matrix[2][2], num[10]), gameNumber(matrix[2][3], num[11]));
	//4-я строка игрового поля
	printf("|        |        |        |        |\n");
	printf("|________|________|________|________|\n");
	printf("|        |        |        |        |\n");
	printf("|  %4s  |  %4s  |  %4s  |  %4s  |\n",
		gameNumber(matrix[3][0], num[12]), gameNumber(matrix[3][1], num[13]),
		gameNumber(matrix[3][2], num[14]), gameNumber(matrix[3][3], num[15]));
	//Информативный блок
	printf("|        |        |        |        |\n");
	printf("|________|________|________|________|\n");
	printf("#===================================#\n");
	printf("#    W,A,S,D - Move; B - Exit       #\n");
	printf("#  Made by Dmitry Shitik 053503     #\n");
	printf("#___________________________________#\n");

	return true;

}

/// Выводит строку num для игрового окна

char* gameNumber(int n, char num[5]) {

	if (n == 0) {							
		num[0] = ' ';
		num[1] = '\0';
	}
	else {
		int buff = (int)pow(2.0, n);			
		_itoa(buff, num, 10);		
	}

	return num;
}

/// Проверка конца игры
bool verificationEndGame(int matrix[SIZE][SIZE]) {

	bool success = false;															//Успешность проверки

	if (!matrix) return false;

	//Проверка концца
	for (int k = 0; k < 4; k++) {													

		//Алгоритм проверки конца, проверка смещений
		for (int i = 0; i < SIZE && !success; i++)							
			for (int j = 0; j < SIZE - 1 && !success; j++)							

				if (matrix[j][i] == 0)												
					for (int k = j + 1; k < SIZE; k++) if (matrix[k][i] != 0)			 
					{	
						success = true;
						break;
					}

		//Алгоритм проверки конца, проверка склеивания
		for (int i = 0; i < SIZE && k < 3 && !success; i++)
			for (int j = 0; j < SIZE - 1 && !success; j++)
				if (matrix[j][i] == matrix[j + 1][i] && matrix[j][i] != NULL) success = true;

		//Поворот матрици
		turnElementsRight(matrix, 1);
	}

	return success;
}

/// Отпечатать экран завершения игры

bool printEndScreen(int matrix[SIZE][SIZE], char name_player[9], int score, int max) {

	system("cls");														

	if (!matrix) return false;

	/// Отрисовка экрана
	printf("_____________________________________\n");
	printf("|             GAME 2048             |\n");
	printf("|        Score:%7d              |\n", score);
	printf("|___________________________________|\n");
	printf("|                                   |\n");
	printf("|                                   |\n");
	printf("|                                   |\n");
	printf("|                                   |\n");
	printf("|                                   |\n");
	printf("|            %9s              |\n", (max == 11) ? "YOU  WIN!" : "GAME OVER");
	printf("|                                   |\n");
	printf("|                                   |\n");
	printf("|      You want play new game?      |\n");
	printf("|                                   |\n");
	printf("|            Press Y\\N.             |\n");
	printf("|                                   |\n");
	printf("|                                   |\n");
	printf("|                                   |\n");
	printf("|                                   |\n");
	printf("|___________________________________|\n");
	printf("#===================================#\n");
	printf("#___________________________________#\n");

	return true;

}