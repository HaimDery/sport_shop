#pragma once
#include<time.h>



typedef struct date {
    int dd, mm, yyyy;
    int hours, minutes;
} date;


void getDateTime(date* DatePtr);
int dateTest(date* date, char enterDate[256]);
int dateCmp(int linked_list_dd_1, int linked_list_mm_1, int linked_list_yyyy_1, int dd_2, int mm_2, int yyyy_2);
struct tm dateToTm(date d);

