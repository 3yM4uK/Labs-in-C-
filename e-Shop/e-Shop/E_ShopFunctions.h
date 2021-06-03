#pragma once

#include "source.h"
#include "struct.h"
#include "BasketListFunctions.h"
#include "BuyerListFunctions.h"
#include "ProductslistFunctions.h"

E_Shop* initShop() {
	E_Shop* e_shop = (E_Shop*)malloc(sizeof(E_Shop));
	e_shop->productList = createProductList();
	e_shop->buyerList = createBuyerList();
	e_shop->currentUser = NULL;
	e_shop->revenue = 0;
	return e_shop;
}

bool userAuthorized(E_Shop* e_shop) {
	return e_shop->currentUser != NULL;
}

void authorize(E_Shop* e_shop) {
	BuyerData buyer;
	if (!userAuthorized(e_shop)) {
		enterBuyerData(&buyer);
		BuyerList_pushBack(e_shop->buyerList, buyer);
		e_shop->currentUser = e_shop->buyerList->tail;
		e_shop->currentUser->basketList = createBasketList();
		e_shop->currentUser->purchaseHistory = createProductList();
		FILE* history = fopen("history.txt", "w");
		fclose(history);
	}
	else {
		system("cls");
		printf("User already authorized!\n");
	}
}

void showBasket(E_Shop* e_shop) {
	if (userAuthorized(e_shop)) {
		showBasketList(e_shop->currentUser->basketList);
	}
	else {
		printf("You're not authorized!\n");
	}
}

void showAmountOfPurchases(E_Shop* e_shop) {
	printf("Amount of purchases: %d\n", e_shop->currentUser->data.amountOfPurchases);
}

void addInBasketNthProduct(E_Shop* e_shop) {
	int n;
	printf("Product list:\n");
	showProductList(e_shop->productList);
	enterInt("Enter index of product you want to add in basket: ", &n);
	Product* finded = getNthProduct(e_shop->productList, n - 1);
	if (finded == NULL) {
		printf("There is no such products!\n");
		return;
	}
	system("cls");
	showProductInfo(finded);
	if (finded->data.isAvailable == inStock) {
		basketList_pushBack(e_shop->currentUser->basketList, finded);
		e_shop->currentUser->data.amountOfPurchases += finded->data.salary;
		printf("This product was succesfully added in basket!\n");
	}
	else {
		printf("This product not in stock!\n");
	}
}

void makePurchase(E_Shop* e_shop, Product* product) {
	int choice;
	system("cls");
	showProductInfo(product);
	enterInt("Are you sure you want to make a purchase?\n1 - yes\n2- no.\n", &choice);
	if (choice == 1) {
		ProductList_pushBack(e_shop->currentUser->purchaseHistory, product->data);
		e_shop->revenue += product->data.salary;
		printf("The purchase was completed successfully!\n");
	}else if(choice == 2){
		system("cls");
		return;
	}
}

void chooseAndBuy(E_Shop* e_shop) {
	int choice;
	printf("Basket list:\n");
	showBasketList(e_shop->currentUser->basketList);
	enterInt("Enter number of product you want to buy: ", &choice);
	Basket* finded = getNthBasket(e_shop->currentUser->basketList, choice);
	if (finded == NULL) {
		system("cls");
		printf("There is no such product in your basket!\n");
		return;
	}
	makePurchase(e_shop, finded->product);
}

void showRevenue(E_Shop* e_shop) {
	printf("E-shop revenue: %d\n", e_shop->revenue);
}

void saveRevenue(E_Shop* e_shop) {
	FILE* file = fopen("revenue.txt", "w");
	fprintf(file, "%d", e_shop->revenue);
}

void loadRevenue(E_Shop* e_shop) {
	FILE* file = fopen("revenue.txt", "r");
	fscanf(file, "%d", &e_shop->revenue);
}

void showMainMenu(E_Shop* e_shop) {
	printf("E-Shop\n");
	printf("1 - Authorize.\n");
	printf("2 - Add products from keyboard.\n");
	printf("3 - Add products from file.\n");
	printf("4 - Show products.\n");
	printf("5 - Add product in basket.\n");
	printf("6 - Make a purchase.\n");
	printf("7 - Show purchase history.\n");
	printf("8 - Show E-Shop revenue.\n");
	printf("9 - Exit.\n");
}

void mainMenu(E_Shop*& e_shop) {
	int choice = 0;
	FILE* file = NULL;
	do {
		showMainMenu(e_shop);
		enterInt("", &choice);
		switch (choice)
		{
		case 1:
			system("cls");
			if (!userAuthorized(e_shop)) {
				authorize(e_shop);
			}
			else {
				system("cls");
				printf("You're already authorized!\n");
			}
			break;
		case 2:
			system("cls");
			if (!userAuthorized(e_shop)) {
				printf("You need to authorize!\n");
				authorize(e_shop);
			}
			system("cls");
			addProductsInList(e_shop->productList);
			writeProductListToFile(e_shop->productList, "list.txt");
			break;
		case 3:
			system("cls");
			if (!userAuthorized(e_shop)) {
				printf("You need to authorize!\n");
				authorize(e_shop);
			}
			system("cls");
			loadRevenue(e_shop);
			enterProductListFromFile(e_shop->productList, "list.txt");
			printf("Products was succesfully added!\n");
			break;
		case 4:
			system("cls");
			if (!userAuthorized(e_shop)) {
				printf("You need to authorize!\n");
				authorize(e_shop);
			}
			system("cls");
			if (!emptyProductList(e_shop->productList)) {
				showProductList(e_shop->productList);
			}
			else {
				printf("List of products is empty!\n"); 
			}
			break;
		case 5:
			system("cls");
			if (!userAuthorized(e_shop)) {
				printf("You need to authorize!\n");
				authorize(e_shop);
			}
			system("cls");
			if (userAuthorized(e_shop)) {
				addInBasketNthProduct(e_shop);
			}
			else {
				printf("You're not authorized!\n");
			}
			break;
		case 6:
			system("cls");
			if (!userAuthorized(e_shop)) {
				printf("You need to authorize!\n");
				authorize(e_shop);
			}
			system("cls");
			if (userAuthorized(e_shop)) {
				chooseAndBuy(e_shop);
				writeProductListToFile(e_shop->currentUser->purchaseHistory, "history.txt");
			}
			else {
				printf("You're not authorized!\n");
			}
			break;
		case 7:
			system("cls");
			if (!userAuthorized(e_shop)) {
				printf("You need to authorize!\n");
				authorize(e_shop);
			}
			system("cls");
			if (userAuthorized(e_shop)) {
				if (!emptyProductList(e_shop->currentUser->purchaseHistory)) {
					printf("Purchase history:\n");
					showProductList(e_shop->currentUser->purchaseHistory);
				}
				else {
					printf("Your purchase history is empty!\n");
				}
			}
			else {
				printf("You're not authorized!\n");
			}
			break;
		case 8:
			system("cls");
			if (!userAuthorized(e_shop)) {
				printf("You need to authorize!\n");
				authorize(e_shop);
			}
			system("cls");
			showRevenue(e_shop);
			break;
		case 9:
			system("cls");
			if (!emptyProductList(e_shop->productList)) {
				writeProductListToFile(e_shop->productList, "list.txt");
			}
			if (!emptyProductList(e_shop->currentUser->purchaseHistory) && userAuthorized(e_shop)) {
				writeProductListToFile(e_shop->currentUser->purchaseHistory, "history.txt");
			}
			saveRevenue(e_shop);
			deleteProductList(&e_shop->productList);
			free(e_shop->currentUser);
			free(e_shop->buyerList);
			free(e_shop->productList);
			free(e_shop);
			return;
		default:
			system("cls");
			printf("There is no such option!\n");
		}
	} while (true);
}





