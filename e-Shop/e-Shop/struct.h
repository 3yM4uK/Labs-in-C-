#pragma once
enum availabillity{inStock, notInStock};

typedef struct ProductData {
	char product[200];
	int salary;
	int guarantee;
	char description[255];
	char originCountry[200];
	availabillity isAvailable;
}ProductData;

typedef struct BuyerName {
	char name[200];
	char surname[200];
	char patronymic[200];
};

typedef struct BuyerContacts {
	char mobilePhone[200];
	char email[200];
}BuyerContacts;

typedef struct BuyerData {
	BuyerContacts contacts;
	BuyerName personalInfo;
	size_t amountOfPurchases;
}BuyerData;

typedef struct Product {
	ProductData data;
	Product* next;
	Product* prev;
}Product;

typedef struct Basket {
	Product* product;
	Basket* next;
	Basket* prev;
};

typedef struct ProductList {
	Product* head;
	Product* tail;
	size_t size;
}ProductList;

typedef struct BasketList {
	Basket* head;
	Basket* tail;
	size_t size;
};

typedef struct Buyer {
	ProductList* purchaseHistory;
	BasketList* basketList;
	BuyerData data;
	Buyer* next;
	Buyer* prev;
}Buyer;

typedef struct BuyerList {
	Buyer* head;
	Buyer* tail;
	size_t size;
}BuyerList;

typedef struct E_Shop {
	ProductList* productList;
	BuyerList* buyerList;
	Buyer* currentUser;
	int revenue;
}E_Shop;
