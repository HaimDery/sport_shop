#pragma once
#include"items1.h"
#include"date.h"
#include "customers.h"

typedef struct Purchase {
    int Recipt_Number;
    int Client_num;
    int catlog_Number;
    int quantity;
    date purchase_date;
    float price;
    struct Purchase* next;
} Purchase;




void addNewPurchase(char number_of_recipt[20], char client_num[20], char catalog_num[20], char quantity[20]);
void WritePurchasesToFile();
void insertPurchasesToList();
void displaypurchase();
void addNewNodeToPurchaseList(int flag, int number_of_recipt, int client_num, int catlog_Number, int quantity, float price, char enterdate[20]);
void handleInsertPurchase();
void handledisplaypurchases();
int Returns14(int ClientNum, int number_of_recipt, struct customers* Customer, int* quantity, int* CatalogNum);
void HandleReturns();
void addToPurchaseFile(Purchase* newnode);
float find_price(int catlog_num, int quntity);
