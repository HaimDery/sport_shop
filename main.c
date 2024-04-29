#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include "employees.h"
#include "customers.h"
#include "items1.h"
#include "menu.h"
#include "Purchases.h"



void main() 
{
    EmployeePreProcessing();
    insertItemsToLinkedList();
    insertcustomersToLinkedList();
    insertEmployeesToLinkedList();
    insertPurchasesToList();
    int level = -1;
    char act[15]="";
    int attempt = 0;


  while (1) {

        /*בלולאה הזאת אנחנו בודקים אם המשתמש הכניס פרטים נכונים. אם הפרטים נכונים הרמה תשתנה לרמה תיקנית כלומר רמה בין 1 ל3 ואז נצא מהלולאה */
        while (level == -1) 
        {
            if (attempt > 2)
            {
                releaseEmployees();
                releaseMembers();
                releaseItems();
                itemLogger("Login", "Third attempt", "Closing the program", "Too many login attempts, exit...");
                return;
            }

            /* כאן אנחנו מבקשים משתמש וסיסמה ובודקים עם הוא תקני. אם כן הפונקציה תחזיר רמה בין 1 ל3 */
            level = login();
            attempt ++;
        }
        printMenu(level);
        /* ð÷ìè ôòåìä îäîùúîù åðùìç ìôåð÷öéä äîúàéîä. */
        scanf("%s",act);

        if (strcmp(act, "1") == 0 && level >= 1)              handleSearchItems();
        else if (strcmp(act, "2") == 0 && level >= 1)         handleInsertItem();
        else if (strcmp(act, "3") == 0 && level >= 1)         handleInsertcustomers();
        else if (strcmp(act, "4") == 0 && level >= 2)         handleUpdateItem();
        else if (strcmp(act, "5") == 0 && level >= 2)         handleDeleteItem();
        else if (strcmp(act, "6") == 0 && level >= 2)         handleUpdatemember();
        else if (strcmp(act, "7") == 0 && level >= 2)         handleDeletemember();
        else if (strcmp(act, "8") == 0 && level >= 3)         displayEmployees();
        else if (strcmp(act, "9") == 0 && level >= 3)         handleAddEmployee();
        else if (strcmp(act, "10") == 0 && level >= 3)        handleUpdateEmployee();
        else if (strcmp(act, "11") == 0 && level >= 3)        handleDeleteEmployee();
        else if (strcmp(act, "12") == 0 && level >= 3)        handleSearchmember();
        else if (strcmp(act, "13") == 0 && level >= 3)        displayItems();
        else if (strcmp(act, "14") == 0 && level >= 3)        displaycustomers();
        else if (strcmp(act, "15") == 0 && level >= 2)        handleInsertPurchase();
        else if (strcmp(act, "16") == 0 && level >= 2)         handledisplaypurchases();
        else if (strcmp(act, "17") == 0 && level >= 2)         HandleReturns();
   
        else
        {
            printf("Exit.... \n");
            //free all the nodes from the memory.
            releaseEmployees();
            releaseMembers();
            releaseItems();
            break;
        }
    }
}
