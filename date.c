#include"date.h"
#include<time.h>

/*פה ההשוואה מתבצעת בפועל. אנחנו משווים שנה מול שנה חודש מול חודש יום מול יום ומחזירים את האתריך הגדול ביותר */
int dateCmp(int linked_list_dd_1, int linked_list_mm_1, int linked_list_yyyy_1, int dd_2, int mm_2, int yyyy_2) 
{
    /* פה אנחנו בודקים אם התאריכים שווים*/
    if (linked_list_dd_1 == dd_2 && linked_list_mm_1 == mm_2 && linked_list_yyyy_1 == yyyy_2)
        return 0;
    /*פה אנחנו בודקים אם התאריך הראשון גדול מהשני*/
    else if (linked_list_yyyy_1 > yyyy_2 ||
        (linked_list_yyyy_1 == yyyy_2 && linked_list_mm_1 > mm_2) ||
        (linked_list_yyyy_1 == yyyy_2 && linked_list_mm_1 == mm_2 && linked_list_dd_1 > dd_2))
        return 1;

    /*אם התאריכים לא שווים וגם התאריך הראשון לא גדול מהשני זה אומר שהתאריך השני גדול מהראשון*/
    else return -1;
}
/* אנחנו משווים בין שני תאריכים, ומחזירים 1 עם התאריך הראשון גדול יותר -1 אם התאריך השני גדול יותר 0 אם האתריכים שווים*/
int dateTest(date* date, char enterDate[256])
{
    /*char tempDate[256];*/
    int dd, mm, yyyy;
    /*strcpy(tempDate, enterDate);*/
    sscanf(enterDate,"%d/%d/%d",&dd, &mm, &yyyy);
    
    return dateCmp(date->dd, date->mm, date->yyyy,dd,mm,yyyy);
}

void getDateTime(date* DatePtr)
{
    time_t rawtime;
    struct tm* timeinfo = (struct tm*)malloc(sizeof(struct tm));

    if (timeinfo == NULL) {
        printf("Error: Memory allocation failed.\n");
        return;
    }

    time(&rawtime);
    localtime_s(timeinfo, &rawtime);

    // Populate the fields of the date struct
    DatePtr->dd = timeinfo->tm_mday;
    DatePtr->mm = timeinfo->tm_mon + 1;
    DatePtr->yyyy = timeinfo->tm_year + 1900;
    DatePtr->hours = timeinfo->tm_hour;
    DatePtr->minutes = timeinfo->tm_min;

    free(timeinfo); // Free the allocated memory when done
}

struct tm dateToTm(date d) {
    struct tm tm_date = { 0 };
    tm_date.tm_year = d.yyyy - 1900; // Years since 1900
    tm_date.tm_mon = d.mm - 1;       // Month (0-indexed)
    tm_date.tm_mday = d.dd;          // Day of the month
    tm_date.tm_hour = 0;      // Hour
    tm_date.tm_min =0;      // Minutes
    return tm_date;
}



//void getDateTime(date* DatePtr)
//{
//    time_t rawtime;
//    struct tm* timeinfo;
//
//    time(&rawtime);
//    timeinfo = localtime(&rawtime);
//
//    // Populate the fields of the date struct
//    DatePtr->dd = timeinfo->tm_mday;
//    DatePtr->mm = timeinfo->tm_mon + 1;
//    DatePtr->yyyy = timeinfo->tm_year + 1900;
//    DatePtr->hours = timeinfo->tm_hour;
//    DatePtr->minutes = timeinfo->tm_min;
//}



//void getDateTime(date* DatePtr)
//{
//    time_t rawtime;
//    struct tm* timeinfo;
//
//    time(&rawtime);
//    timeinfo = localtime(&rawtime);
//
//    // Check if localtime failed (returned NULL)
//    if (timeinfo == NULL)
//    {
//        // Handle the error, maybe print a message and return
//        printf("Error: Unable to get local time.\n");
//        return;
//    }
//    // Populate the fields of the date struct
//    DatePtr->dd = timeinfo->tm_mday;
//    DatePtr->mm = timeinfo->tm_mon + 1;
//    DatePtr->yyyy = timeinfo->tm_year + 1900;
//    DatePtr->hours = timeinfo->tm_hour;
//    DatePtr->minutes = timeinfo->tm_min;
//}





