#pragma once

#include <stdbool.h>
#include"date.h"




typedef struct item {
    int Catlog_Number;
    char brand[20]; // can edit name
    char description[20]; // can edit name
    float price;
   int inventory;
    int quantity;
    // char date[11];
    date date;
    struct item* next;
} item;

item* HeadPtr;
void printResult1(item* temp);
void WriteItemsToFile();
void addNewItem(char Catalog_Number[20], char brand[20], char Price[20], char Description[20], char inventory[20]);
void insertItemsToLinkedList();
void searchItems(int op, char str1[256], char str2[256]);
int deleteItem(int Catalog_Number);
int updateItem(char Catalog_Number[20], char brand[20], char Price[20], char Description[20], char inventory[20]);
void displayItems();
void handleSearchItems();
void handleInsertItem();
void handleUpdateItem();
void getDateTime(date* DatePtr);
void handleDeleteItem();
void releaseItems();
void AddItemToFile(item* newnode);
void addNewNodeToItem(int flag, int Catalog_Number, char brand[20], float Price, char Description[20], int inventory, char enterdate[20]);
void itemLogger(char act[50], char att[40], char value[40], char msg[256]);
void updateInventory(int Catalog_Number, int NumOfReturns, int flag);


