#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <conio.h>
#include <assert.h>

char* enterStr();

bool letter(char symbol);
bool sentenceCompletion(char symbol);
bool punctuation(char symbol);
char* fixCapitalLetters(char* str);
size_t countSentences(char* str);
char* fixSpaces(char* str);
char* fixSentence(char* str);
void enterText(char** text, int lines);
void fixText(char** text, int lines);
void showText(char** text, int lines);