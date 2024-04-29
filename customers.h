#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "date.h"
#include "items1.h"
#include"customers.h"
#include"Purchases.h"


// Define struct for Customer
typedef struct customers 
{
    int number;
    char full_name[20];
    char date_of_create[20];
    char id[10];
    int items_purchased;
    date date;
    Purchase* purchases_head; // Pointer to the head of the purchases linked list
    struct customers* next;
} customers;

customers* head;

void addNewNodeToMem(int flag, int number, char full_name[20], char id[10], int items_purchased, char enterdate[20]);
void insertcustomersToLinkedList();//ôåð÷öéä ìäëðñú ì÷åçåú ìøùéîä î÷åùøú 
int deletecustomers(int memberToDelete);
void addNewcustomers(char number[20], char full_name[20], char id[10], char items_purchased[20]);
int updatecustomers(char number[20], char full_name[20], char id[10], char items_purchased[20]);
void displaycustomers();//ôåð÷öééú ìäöâú ì÷åçåú
void handleInsertcustomers();//ôåð÷öééú ìäëðñä ùì ì÷åçåú ì÷åáõ
void handleDeletemember();//ôåð÷öééú ì÷áìú îñôø ì÷åç òì îðú ìîçå÷ àåúå
void handleUpdatemember();//ôåð÷öééú ìäãôñú îéãò ùì äì÷åçåú, îëðéñéí ÷ìè åîòãëðéí
void handleSearchmember();
void searchmember(int op, char str1[256], int member_number);
void removeMemberWithValue(customers* nodeToRemove);
void printResult(customers*head);
void releaseMembers();
void AddMemToFile(customers* newnode);
void writecustomersToFile();
customers* findCustomer(int x);




