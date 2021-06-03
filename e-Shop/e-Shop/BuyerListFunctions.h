#pragma once
#include "BasketListFunctions.h"
#include "source.h"
#include "struct.h"

BuyerList* createBuyerList() {
	BuyerList* tmp = (BuyerList*)malloc(sizeof(BuyerList));
	tmp->head = tmp->tail = NULL;
	tmp->size = 0;
	return tmp;
}

bool emptyBuyerList(BuyerList* list) {
	return list == NULL;
}

void deleteBuyerList(BuyerList** list) {
	Buyer* tmp = (*list)->head;
	Buyer* next = NULL;
	while (tmp) {
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	(*list)->head = (*list)->tail = NULL;
}

void BuyerList_pushBack(BuyerList* list, BuyerData data) {
	Buyer* tmp = (Buyer*)malloc(sizeof(Buyer));
	if (tmp == NULL) {
		exit(-101);
	}
	tmp->basketList = createBasketList();
	tmp->data = data;
	tmp->next = NULL;
	tmp->prev = list->tail;
	if (list->tail != NULL) {
		list->tail->next = tmp;
	}
	list->tail = tmp;
	if (list->head == NULL) {
		list->head = tmp;
	}
	list->size++;
}

void enterBuyerData(BuyerData* data) {
	printf("Enter name: ");
	rewind(stdin);
	gets_s(data->personalInfo.name);
	printf("Enter surname: ");
	rewind(stdin);
	gets_s(data->personalInfo.surname);
	printf("Enter patronymic: ");
	rewind(stdin);
	gets_s(data->personalInfo.patronymic);
	printf("Enter phone number: ");
	rewind(stdin);
	gets_s(data->contacts.mobilePhone);
	printf("Enter e-mail: ");
	rewind(stdin);
	gets_s(data->contacts.email);
	data->amountOfPurchases = 0;
}

void showBuyerData(Buyer* buyer) {
	printf(" _________________________________________________________________\n");
	printf("|   Name       |%50s|\n", buyer->data.personalInfo.name);
	printf("|______________|__________________________________________________|\n");
	printf("|   Surname    |%50s|\n", buyer->data.personalInfo.surname);
	printf("|______________|__________________________________________________|\n");
	printf("|   Patronymic |%50s|\n", buyer->data.personalInfo.patronymic);
	printf("|______________|__________________________________________________|\n");
	printf("|   E-mail     |%50s|\n", buyer->data.contacts.email);
	printf("|______________|__________________________________________________|\n");
	printf("|   Phone      |%50s|\n", buyer->data.contacts.mobilePhone);
	printf("|______________|__________________________________________________|\n");
}


