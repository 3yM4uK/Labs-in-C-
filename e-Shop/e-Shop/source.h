#pragma once
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

void enterInt(const char* instruction, int* value) {
	do {
		printf("%s", instruction);
		if (scanf_s("%d", &*value)) {
			return;
		}
		else {
			system("cls");
			rewind(stdin);
			printf("Incorrect input!\n");
		}
	} while (true);
}