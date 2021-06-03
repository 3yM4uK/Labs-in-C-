#include "main.h"

#pragma warning(disable:4996)

char* enterStr() {
    char* str = (char*)malloc(sizeof(char*));
    if (str == NULL) {
        exit(-101);
    }
    int i = 0;
    while ((str[i] = getchar()) != '\n') {
        str = (char*)realloc(str, (++i + 1) * sizeof(char*));
        if (str == NULL) {
            free(str);
            exit(-101);
        }
    }
    str[i + 1] = '\0';
    return str;
}

bool letter(char symbol) {
    return ((symbol >= 'a' && symbol <= 'z') || (symbol >= 'A' && symbol <= 'Z')) ? true : false;
}

bool sentenceCompletion(char symbol) {
    return (symbol == '?' || symbol == '!' || symbol == '.') ? true : false;
}

bool punctuation(char symbol) {
    return (symbol == ',' || symbol == ':' || symbol == ';') ? true : false;
}

char* fixCapitalLetters(char* str) {
    if (str == NULL) {
        return NULL;
    }
    int i = 0;
    while (!letter(str[i])) {
        i++;
    }
    str[i] = toupper(str[i]);
    for (i = 1; str[i] != '\0'; i++)
    {
        if (sentenceCompletion(str[i])) {
            while (!letter(str[i])) {
                i++;
            }
            str[i] = toupper(str[i]);
        }
    }
    return str;
}

size_t countSentences(char* str) {
    size_t counter = 0;
    int i = 0;
    while (str[i] != '\0') {
        if (sentenceCompletion(str[i])) {
            counter++;
        }
        i++;
    }
    return counter;
}

char* fixSpaces(char* str) {
    if (str == NULL) {
        return NULL;
    }
    int punct = countSentences(str);
    char* fixedString = (char*)malloc(strlen(str) + punct);
    if (fixedString == NULL) {
        exit(-101);
    }
    int i = 0, j = 0;
    while (str[i] != '\0') {
        if ((sentenceCompletion(str[i]) || punctuation(str[i])) && str[i + 1] != ' ') {
            fixedString[j] = str[i];
            j++;
            fixedString[j] = ' ';
        }
        else {
            fixedString[j] = str[i];
        }
        i++; j++;
    }
    fixedString[j] = '\0';
    return fixedString;
}

char* fixSentence(char* str) {
    str = fixCapitalLetters(str);
    str = fixSpaces(str);
    return str;
}

void enterText(char** text, int lines) {
    printf("Enter something:\n");
    int i;
    for (i = 0; i < lines; i++) {
        rewind(stdin);
        text[i] = enterStr();
    }
}

void fixText(char** text, int lines) {
    if (text == NULL) {
        return;
    }
    int i;
    for (i = 0; i < lines; i++) {
        text[i] = fixCapitalLetters(text[i]);
        text[i] = fixSpaces(text[i]);
    }
}
void showText(char** text, int lines) {
    if (text == NULL) {
        return;
    }
    int i;
    for (i = 0; i < lines; i++) {
        printf("%s", text[i]);
    }
}

int main() {
    SetConsoleCP(1251);
    int lines = 0;
    char** text = NULL;
    printf("Enter how many lines should be created: ");
    scanf("%d", &lines);
    system("cls");
    text = (char**)malloc(lines * sizeof(char*));
    if (text == NULL) {
        exit(-101);
    }
    enterText(text, lines);
    system("cls");
    printf("Before changing:\n");
    showText(text, lines);
    putchar('\n');
    fixText(text, lines);
    printf("After changin:\n");
    showText(text, lines);
    free(text);
    getch();
}