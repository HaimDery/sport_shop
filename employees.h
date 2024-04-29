#pragma once
#include"date.h"
#include<stdio.h>
#include<stdlib.h>
#include"items1.h"


typedef struct Employee 
{
    char username[20];
    char Full_Name[25];
    char password[10];
    unsigned int level; // 1 - admin, 2 - employee, 3 - practicioner
    date date;
    struct Employee* next;
} Employee;

int userAdd;

Employee* HeadP;
int login();//done
char* trimespaces(char* str);//done
void EmployeePreProcessing();//done
void releaseEmployees();//done
void insertEmployeesToLinkedList();//done
int deleteEmployee(char employToDelete[20]);//done
void removeNodeWithValue(Employee* nodeToRemove);//done
void displayEmployees();//done
void addEmployee2File(char username[15], char password[15], char level[3], char fullname[25]);//done
Employee* FindEmployee(const char value[20]);//done
int addNewEmployee(char username[15], char password[15], char fullname[25], char level[3]);//done
void handleAddEmployee();//done
void handleUpdateEmployee();//done
void handleDeleteEmployee();//done
void getDateTime(date* DatePtr);








//emplyoee_edit();//edit employee,erase emplyoee or add new employee.
//erase_employee();//erase employee by ersat him from the employee file.
//add_new_employee();//edd new worker and write all of his data in the file(name,id,user name,paswword,level).









