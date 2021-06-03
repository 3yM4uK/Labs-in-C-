#pragma once
#include "source.h"
#include "struct.h"
#pragma	warning(disable: 4996)
#pragma once

ProductList* createProductList() {
	ProductList* tmp = (ProductList*)malloc(sizeof(ProductList));
	tmp->head = tmp->tail = NULL;
	tmp->size = 0;
	return tmp;
}

void deleteProductList(ProductList** list) {
	Product* tmp = (*list)->head;
	Product* next = NULL;
	while (tmp) {
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	(*list)->head = (*list)->tail = NULL;
}

bool emptyProductList(ProductList* list) {
	return (!list->head || !list->tail) ? true : false;
}

void ProductList_pushBack(ProductList* list, ProductData data) {
	Product* tmp = (Product*)malloc(sizeof(Product));
	if (tmp == NULL) {
		exit(-101);
	}
	tmp->data = data;;
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

void* popBack(ProductList* list, size_t data_type) {
	Product* next;
	void* tmp = NULL;
	if (list->tail == NULL) {
		exit(-102);
	}
	next = list->tail;
	list->tail = list->tail->prev;
	if (list->tail != NULL) {
		list->tail->next = NULL;
	}
	if (next == list->head) {
		list->head = NULL;
	}
	memcpy(tmp, &next->data, data_type);
	free(next);
	list->size--;
	return tmp;
}

Product* getNthProduct(ProductList* list, size_t index) {
	Product* tmp = NULL;
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

void deleteNthProduct(ProductList* list, size_t index) {
	Product* elm = NULL;
	void* tmp = NULL;
	elm = getNthProduct(list, index);
	if (elm == NULL) {
		return;
	}
	if (elm->prev) {
		elm->prev->next = elm->next;
	}
	if (elm->next) {
		elm->next->prev = elm->prev;
	}
	if (!elm->prev) {
		list->head = elm->next;
	}
	if (!elm->next) {
		list->tail = elm->prev;
	}
	free(elm);
	list->size--;
}

void showProductInfo(Product* product) {
	const char* available = "available";
	const char* unavailable = "unavailable";
	printf(" ______________________________________________________________________\n");
	printf("|   Product         |%50s|\n", product->data.product);
	printf("|___________________|__________________________________________________|\n");
	printf("|   Salary          |%50d|\n", product->data.salary);
	printf("|___________________|__________________________________________________|\n");
	printf("|  Description      |%50s|\n", product->data.description);
	printf("|___________________|__________________________________________________|\n");
	printf("|  Origin country   |%50s|\n", product->data.originCountry);
	printf("|___________________|__________________________________________________|\n");
	printf("|  Guarantee        |%50d|\n", product->data.guarantee);
	printf("|___________________|__________________________________________________|\n");
	if (product->data.isAvailable == inStock) {
		printf("|  Availability     |%50s|\n", available);
	}
	else if (product->data.isAvailable == notInStock) {
		printf("|  Availability     |%50s|\n", unavailable);
	}
	printf("|___________________|__________________________________________________|\n");
}

void enterProduct(ProductData* product) {
	int choice;
	printf("Enter name of product: ");
	rewind(stdin);
	gets_s(product->product);
	enterInt("Enter salary: ", &product->salary);
	printf("Enter description: ");
	rewind(stdin);
	gets_s(product->description);
	printf("Enter origin country of this product: ");
	rewind(stdin);
	gets_s(product->originCountry);
	enterInt("Enter guarantee(years): ", &product->guarantee);
	do {
		printf("Is product in stock right now?\n");
		printf("1 - yes.\n");
		printf("2 - no.\n");
		if (scanf_s("%d", &choice)) {
			switch (choice)
			{
			case 1:
				product->isAvailable = inStock;
				return;
			case 2:
				product->isAvailable = notInStock;
				return;
			default:
				printf("There is no such option!\n");
			}
		}
		else {
			rewind(stdin);
			printf("Incorrect input!\n");
		}
	} while (true);
}

void addProductsInList(ProductList* list) {
	int list_size;
	ProductData product;
	enterInt("How many products you want to add?\n", &list_size);
	for (int i = 0; i < list_size; i++, system("cls")) {
		printf("Product #%d:\n", i + 1);
		rewind(stdin);
		enterProduct(&product);
		ProductList_pushBack(list, product);
	}
}

void showProductList(ProductList* list) {
	Product* tmp = list->head;
	int counter = 0;
	while (tmp) {
		printf("Product %d:\n", counter + 1);
		showProductInfo(tmp);
		tmp = tmp->next;
		counter++;
	}
}

void writeProduct(Product* product, FILE* file) {
	fprintf(file, "%d ", strlen(product->data.product));
	fprintf(file, "%s ", product->data.product);
	fprintf(file, "%d ", product->data.salary);
	fprintf(file, "%d ", strlen(product->data.description));
	fprintf(file, "%s ", product->data.description);
	fprintf(file, "%d ", strlen(product->data.originCountry));
	fprintf(file, "%s ", product->data.originCountry);
	fprintf(file, "%d ", product->data.guarantee);
	int condition = (product->data.isAvailable == inStock ? 0 : 1);
	fprintf(file, "%d\n", condition);
}

void writeProductListToFile(ProductList* list, const char* filename) {
	FILE* file = fopen(filename, "w");
	if (file == NULL) {
		exit(-101);
	}
	Product* tmp = list->head;
	while (tmp) {
		writeProduct(tmp, file);
		tmp = tmp->next;
	}
	fclose(file);
}

void enterProductListFromFile(ProductList* list, const char* filename){
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		printf("File is empty! Add some products from keyboard and they will be saved to file.\n");
		exit(-101);
	}
	int size = 0;
	char c;
	fscanf(file, "%c", &c);
	while (!feof(file)){
		fscanf(file, "%c", &c);
		if (c == '\n') {
			++size;
		}
	}
	rewind(file);
	int lenght = 0;
	int condition = 0;
	ProductData buffer; 
	for (int i = 0; i < size - 1 && !feof(file); i++) {
		fscanf(file, "%d", &lenght);
		fgets(buffer.product, lenght + 2, file);
		fscanf(file, "%d", &buffer.salary);
		fscanf(file, "%d", &lenght);
		fgets(buffer.description, lenght + 2, file);
		fscanf(file, "%d", &lenght);
		fgets(buffer.originCountry, lenght + 2, file);
		fscanf(file, "%d", &buffer.guarantee);
		fscanf(file, "%d", &condition);
		buffer.isAvailable = (condition == 0) ? inStock : notInStock;
		ProductList_pushBack(list, buffer);
	}
	fclose(file);
}
