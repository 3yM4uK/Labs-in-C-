#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

#pragma warning(disable: 4996)


bool bracket(char symbol) {
    return (
        symbol == '(' || symbol == ')' ||
        symbol == '{' || symbol == '}' ||
        symbol == '[' || symbol == ']') ? true : false;
}

bool openBracket(char symbol) {
    return (
        symbol == '(' ||
        symbol == '[' ||
        symbol == '{') ? true : false;
}

bool closeBracket(char symbol) {
    return (
        symbol == ')' ||
        symbol == ']' ||
        symbol == '}'
        ) ? true : false;
}

char getCloseBracket(char symbol) {
    if (!openBracket(symbol)) {
        exit(-102);
    }
    if (symbol == '(') {
        return ')';
    }
    if (symbol == '{') {
        return '}';
    }
    if (symbol == '[') {
        return ']';
    }
}

int strlenght(char* str) {
    int i = 0;
    while (str[i] != 0)
        i++;
    return i;
}
int bracketLevel(char* string, int index) {
    int level;
    if (openBracket(string[index]))
        level = 0;
    else if (closeBracket(string[index]))
        level = 1;
        int i;
    for (i = index; string[i] != '\0'; i++) {
        if (openBracket(string[i]))
            level++;
        else if (closeBracket(string[i]))
            level--;
    }
    return level;
}
bool correctBracketBalance(char* string) {
    int brackets = 0;
    char openBrack;
    int i;
    for (i = 0; string[i] != '\0'; i++) {
        if (openBracket(string[i])) {
            brackets++;
        }
        else if (closeBracket(string[i])) {
            brackets--;
        }
    }
    return (brackets == 0) ? true : false;
}

void changeBrackets(char* string) {
    if (!correctBracketBalance(string)) {
        return;
    }
    int i;
    for (i = 0; string[i] != '\0'; i++) {
        if (bracket(string[i])) {
            if (bracketLevel(string, i) == 1 || bracketLevel(string, i) == -1) {
                if (openBracket(string[i]))
                    string[i] = '[';
                else if (closeBracket(string[i]))
                    string[i] = ']';
            }
            else if (bracketLevel(string, i) >= 2 || bracketLevel(string, i) <= -2) {
                if (openBracket(string[i]))
                    string[i] = '{';
                else if (closeBracket(string[i]))
                    string[i] = '}';
            }
        }
    }
}

FILE* enterFileInfo(FILE* file, const char* filename) {
    char buffer[500];
    file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return NULL;
    }
    printf("If you want to stop, print 'exit'.\n");
    while (true) {
        printf("Enter line: ");
        rewind(stdin);
        gets(buffer);
        if (!strcmp(buffer, "exit")) {
            break;
        }
        fprintf(file, "%s\n", buffer);
    }
    fclose(file);
    return file;
}

void showFileInfo(FILE* file, const char* filename) {
    char buffer[500];
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    while ((fgets(buffer, 500, file)) != NULL) {
        printf("%s", buffer);
    }
    fclose(file);
}

FILE* changeBracketsInFile(FILE* file, const char* filename) {
    char buffer[500];
    file = fopen(filename, "r+");
    if (file == NULL) {
        printf("Error opening file!\n");
        return NULL;
    }
    while ((fgets(buffer, 500, file) != NULL)) {
        changeBrackets(buffer);
        fseek(file, -strlenght(buffer) - 1, SEEK_CUR);
        fprintf(file, "%s", buffer);
        fseek(file, strlenght(buffer), SEEK_CUR);
    }
    fclose(file);
    return file;
}

int main() {
    FILE* filePointer = NULL;
    char filename[30];
    printf("Enter name of file to work with: ");
    rewind(stdin);
    gets(filename);
    enterFileInfo(filePointer, filename);
    system("cls");
    printf("Before changing:\n");
    showFileInfo(filePointer, filename);
    changeBracketsInFile(filePointer, filename);
    putchar('\n');
    printf("After changing:\n");
    showFileInfo(filePointer, filename);
}