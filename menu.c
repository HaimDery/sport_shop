/*מדפיסים את האופציות לפי הרמה במסך הראשי */
void printMenu(int level)
{
    printf("\nPlease choose an action from the following options by inserting the relevant number :\n");
    if (level >= 1)  printf("  0 - Exit\n  1 - Search item\n  2 - Add an item\n  3 - Add an member\n");
    if (level >= 2) printf("  4 - Update an Item\n  5 - Delete an item\n  6 - Update an member\n  7 - Delete an member\n");
    if (level == 3) printf("  8 - Display all the Employees\n  9 - Add an employee\n 10 - Update a employee\n 11 - Delete a employee\n 12 - Search member\n 13 - Display all the item\n 14 - Display all the member\n" );
    if (level >= 2)  printf(" 15 - Add a purchase  \n 16 - View purchases  \n");
    if (level == 3) printf(" 17 - Update a purchase\n");
}
