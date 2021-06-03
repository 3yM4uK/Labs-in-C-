#pragma once

#include "source.h"
#include "struct.h"
#include "ProductslistFunctions.h"

BasketList* createBasketList() {
	BasketList* tmp = (BasketList*)malloc(sizeof(BasketList));
	if (tmp == NULL) {
		exit(5);
	}
	tmp->head = NULL;
	tmp->tail = NULL;
	tmp->size = 0;
	return tmp;
}

void deleteBasketList(BasketList** list) {
	Basket* tmp = (*list)->head;
	Basket* next = NULL;
	while (tmp) {
		next = tmp->next;
		free(tmp->product);
		free(tmp);
		tmp = next;
	}
	(*list)->head = (*list)->tail = NULL;
}

bool emptyBasketList(BasketList* list) {
	return (!list->head || !list->tail) ? true: false;
}
Basket* getNthBasket(BasketList* list, size_t index) {
	Basket* tmp = NULL;
	size_t i;
	if (index < list->size / 2) {
		i = 0;
		tmp = list->head;
		while (tmp && i < index) {
			tmp = tmp->next;
			i++;
		}
	}
	else {
		i = list->size - 1;
		tmp = list->tail;
		while (tmp && i > index) {
			tmp = tmp->prev;
			i--;
		}
	}
	return tmp;
}

void basketList_pushBack(BasketList* list, Product* product) {
	Basket* tmp = (Basket*)malloc(sizeof(Basket));
	if (tmp == NULL) {
		exit(-101);
	}
	tmp->product = product;
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

void showBasketList(BasketList* list){
	Basket* tmp = list->head;
	int counter = 0;
	while (tmp) {
		printf("Product %d:\n", counter + 1);
		showProductInfo(tmp->product);
		tmp = tmp->next;
		counter++;
	}
}

Basket* getBasketByName(BasketList* list, char* name) {
	Basket* tmp = list->head;
	while (tmp) {
		if (!strcmp(tmp->product->data.product, name)) {
			return tmp;
		}
		tmp = tmp->next;
	}
	return NULL;
}

Basket* getBasketBySalary(BasketList* list, int salary) {
	Basket* tmp = list->head;
	while (tmp) {
		if (tmp->product->data.salary == salary) {
			return tmp;
		}
		tmp = tmp->next;
	}
	return NULL;
}

Basket* getBasketByDescription(BasketList* list, char* description) {
	Basket* tmp = list->head;
	while (tmp) {
		if (!strcmp(tmp->product->data.description, description)) {
			return tmp;
		}
		tmp = tmp->next;
	}
	return NULL;
}

Basket* getBasketByOriginCountry(BasketList* list, char* originCountry) {
	Basket* tmp = list->head;
	while (tmp) {
		if (!strcmp(tmp->product->data.originCountry, originCountry)) {
			return tmp;
		}
		tmp = tmp->next;
	}
	return NULL;
}

Basket* getBasketByGuarantee(BasketList* list, int guarantee) {
	Basket* tmp = list->head;
	while (tmp) {
		if (tmp->product->data.guarantee == guarantee) {
			return tmp;
		}
		tmp = tmp->next;
	}
	return NULL;
}


