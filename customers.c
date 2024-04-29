#define _CRT_SECURE_NO_WARNINGS
#include "customers.h"
#include "items1.h"
#include "employees.h"
#include "Purchases.h"
#include"date.h"


/*פה אנחנו עוברים על הרשימה המקושרת וכותבים הכל לקובץ הלקוחות מחדש וככה אנחנו מבטיחים שהסדר ישמר בקובץ הלקוחות כי הרשימה המקושרת ממויינת בעצמה*/
void writecustomersToFile()
{
    struct customers* cur = head;
    FILE* fp = fopen("members.txt", "w");
    fprintf(fp, "%-20s %-20s %-20s %-20s %-20s ", "number", "full_name", "id", "items_pursed", "enterDate");
    while (cur != NULL) {
        fprintf(fp, "\n%-20d %-20s %-20s %-20d %02d/%02d/%d", cur->number, cur->full_name, cur->id, cur->items_purchased, cur->date.dd, cur->date.mm, cur->date.yyyy);
        cur = cur->next;
    }
    fclose(fp);
}


//function that take data from the node that created and update the file
void AddMemToFile(customers* newnode)
{
    FILE* fp = fopen("members.txt", "a+");
    time_t t = time(NULL);
    struct tm* tm_info = localtime(&t);
    char dateFormatted[20];

    if (fp == NULL) {
        printf("Cannot open the file!\n");
        return;
    }

    // Format the date to "dd/mm/yyyy"
    strftime(dateFormatted, sizeof(dateFormatted), "%d/%m/%Y", tm_info);

    //If the item is the first one to enter.
    if (newnode->number == 1)
    {
        fprintf(fp, "%-20s %-20s %-20s %-20s %-20s", "Membernumber", "Fullname", "id", "items_purchased", "Date");
        fprintf(fp, "\n%-20d %-20s %-20s %-20d %-20s", newnode->number, newnode->full_name, newnode->id, newnode->items_purchased, dateFormatted);
        fclose(fp);
    }
    else {
        fprintf(fp, "\n%-20d %-20s %-20s %-20d %-20s", newnode->number, newnode->full_name, newnode->id, newnode->items_purchased, dateFormatted);
        fclose(fp);
    }
}

/*הדפסה של לקוח מהלינקליסט*/
void printResult(customers* head)
{
    printf("\n%-20d %-20s %-20s %-20s %-20d %d/%d/%d", head->number, head->full_name, head->date_of_create, head->id, head->items_purchased, head->date.dd, head->date.mm, head->date.yyyy);
}

//Adding new item(to the linkedlist & text file)
void addNewNodeToMem(int flag, int Membernumber, char full_name[20], char id[10], int items_purchased, char enterdate[20])
{
    /* יוצרים מצביע למקום בגודל של נוד כאשר נוד זה לקוח */
    customers* newNode = (customers*)malloc(sizeof(customers));

    if (newNode == NULL)
    {
        printf("error with allocation of the memory!\n");
        free(newNode);
        return;
    }
    //entering the data to the node.
    newNode->number = Membernumber;
    strcpy(newNode->full_name, full_name);
    strcpy(newNode->id, id);
    newNode->items_purchased = items_purchased;
    newNode->purchases_head = NULL;



    //If item exisisted in the file
    if (flag != 1)
    {
        //getting the original date from the file
        sscanf(enterdate, "%d/%d/%d", &(newNode->date.dd), &(newNode->date.mm), &(newNode->date.yyyy));
    }

    else //means that the item didnt exists in the file.
    {

        //get the date into the node.
        getDateTime(&newNode->date);
        //update the file.
        AddMemToFile(newNode);
    }

    /* Our linked list is sorted by the number (because it is the first data we get from the user) of the item, in ascending order. When inserting a new node, we want to maintain this order. */
    if (head == NULL)/*chack if the head is null.if not we skip on that if.*/
    {
        head = newNode;
        newNode->next = NULL;
    }
    else
    {
        customers* current = head;
        while (current->next != NULL && newNode->number > current->next->number)
        {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}


void insertcustomersToLinkedList()
{
    /* הפונקציה קוראת את הקובץ הלקוחות ועוברת שורה שורה ומכניסה כל שורה ללינקליסט */
    FILE* fp = fopen("members.txt", "r");
    if (fp == NULL)
        return;

    char buffer[256] = "";

    fgets(buffer, 256, fp);

    while (fgets(buffer, 256, fp))
    {
        char number[20] = "", full_name[20] = "", id[10] = "", items_purchased[20] = "", enterDate[21] = "";
        /* בשורות הבאות אנחנו מכניסים מידע מהטקסט למשתנים. שאותם אנחנו מכניסים ללינקליסט.  */
        strncat(number, buffer + 0, 20 - 1);
        strncat(full_name, buffer + 21, 20 - 1);
        strncat(id, buffer + 42, 10 - 1);
        strncat(items_purchased, buffer + 53, 20 - 1);
        strncat(enterDate, buffer + 74, 20 );
        int* dd, mm, yyyy;
        sscanf(enterDate, "%d/%d/%d", &dd, &mm, &yyyy);

        
        addNewNodeToMem(0, atoi(number), trimespaces(full_name), id, atoi(items_purchased), enterDate);
    }

    fclose(fp);
}

/*פה אנחנו מעדכנים גם לרשימה המקושרת וגם לקובץ עצמו*/
void addNewcustomers(char full_name[20], char id[10], char items_purchased[5])
{
    int Membernumber = getNextCustomerNumber();
    /*פה אנחנו מכניסים לרשימה המקושרת*/
    addNewNodeToMem(1, Membernumber, trimespaces(full_name), id, atoi(items_purchased), "geting date");
}

//בדיקה האם קיים אותו לקוח עם אותו תעודת זהות זהה להוספה של לקוח חדש
customers* searchmember(int op, char str1[256], int member_number)
{
    customers* cur = head;
    while (cur != NULL) {
        if (op == 2 && (strcmp(str1, cur->id) == 0))
            return cur;
        cur = cur->next;
    }
    return NULL;
}
//הכנסה אוטומטית של מספר לקוח 
int getNextCustomerNumber() {
    FILE* fp = fopen("members.txt", "r");
    if (fp == NULL) {
        return 1; // Start with 1 if the file doesn't exist
    }

    int number = 0;
    char line[256];
    while (fgets(line, sizeof(line), fp) != NULL) {
        sscanf(line, "%d", &number);
    }
    fclose(fp);

    return number + 1; // Increment the last number by 1
}

//פונקציית לחיפוש לקוחות על פי אופן חיפוש הדרוש
int handleSearchmember() {
    printf("Please insert the required search option:\n");
    printf(" 1 - Full Name and Member Number\n 2 - Full Name\n 3 - ID\n 4 - Full Name and ID\n");

    int flag;
    scanf("%d", &flag);

    switch (flag) {
    case 1: {
        printf("Please enter Full Name and Member Number separated by a space:\n");
        char fullname[20];
        int Membernumber;
        scanf("%s %d", fullname, &Membernumber);

        // Traverse the linked list and print nodes that match the choosen search.
        customers* cur = head;
        printf("%-20s %-20s %-20s %-20s %-20s\n", "Number", "Full Name", "ID", "Items Purchased", "Enter Date");
        while (cur != NULL) {
            if (strcmp(fullname, cur->full_name) == 0 && Membernumber == cur->number)
                printf("%-20d %-20s %-20s %-20d %02d/%02d/%04d\n", cur->number, cur->full_name, cur->id, cur->items_purchased, cur->date.dd, cur->date.mm, cur->date.yyyy);
            cur = cur->next;
        }
        break;
    }
    case 2: {
        printf("Please enter the Full Name:\n");
        char fullname[20];
        scanf("%s", fullname);


        customers* cur = head;
        printf("%-20s %-20s %-20s %-20s %-20s\n", "Number", "Full Name", "ID", "Items Purchased", "Enter Date");
        while (cur != NULL) {
            if (strcmp(fullname, cur->full_name) == 0)
                printf("%-20d %-20s %-20s %-20d %02d/%02d/%04d\n", cur->number, cur->full_name, cur->id, cur->items_purchased, cur->date.dd, cur->date.mm, cur->date.yyyy);
            cur = cur->next;
        }
        break;
    }
    case 3: {
        printf("Please enter the ID:\n");
        char id[10];
        scanf("%s", id);

        customers* cur = head;
        printf("%-20s %-20s %-20s %-20s %-20s\n", "Number", "Full Name", "ID", "Items Purchased", "Enter Date");
        while (cur != NULL) {
            if (strcmp(id, trimespaces(cur->id)) == 0)
                printf("%-20d %-20s %-20s %-20d %02d/%02d/%04d\n", cur->number, cur->full_name, cur->id, cur->items_purchased, cur->date.dd, cur->date.mm, cur->date.yyyy);
            cur = cur->next;
        }
        break;
    }
    case 4: {
        printf("Please enter the Full Name and ID separated by a space:\n");
        char fullname[20], id[10];
        scanf("%s %s", fullname, id);

       
        customers* cur = head;
        printf("%-20s %-20s %-20s %-20s %-20s\n", "Number", "Full Name", "ID", "Items Purchased", "Enter Date");
        while (cur != NULL) {
            if (strcmp(fullname, cur->full_name) == 0 && strcmp(id, trimespaces(cur->id)) == 0)
                printf("%-20d %-20s %-20s %-20d %02d/%02d/%04d\n", cur->number, cur->full_name, cur->id, cur->items_purchased, cur->date.dd, cur->date.mm, cur->date.yyyy);
            cur = cur->next;
        }
        break;
    }
    default:
        printf("Invalid option.\n");
    }
}
//*כדי לעדכן לקוח אנחנו נמחק את הלקוח הקיים ונכניס את אותו הלקוח עם המידע המעודכן.אנחנו נעשה את פעולת ההכנסה רק אם הצלחנו למחוק* /
int updatecustomers(char number[20], char full_name[20], char id[10], char items_purchased[20])
{
    if (deletecustomers(atoi(number)))
    {
        addNewcustomers(number, full_name, id, items_purchased);
        return 1;
    }
    return 0;
}

/*כאן אנחנו מציגים את כל הלקוחות. אנחנו פותחים את קובץ הלקוחות ועוברים שורה שורה ומדפיסים*/
void displaycustomers()
{
    FILE* file = fopen("members.txt", "r");
    if (file == NULL) return;
    char buffer[256] = "";
     itemLogger("Display", "member", "All", "");
     
    while (fgets(buffer, 256, file) != NULL)
    {
        char number[20] = "", full_name[20] = "", id[10] = "", items_purchased[20] = "", enterDate[21] = "";
        /* בשורות הבאות אנחנו מכניסים מידע מהטקסט למשתנים. שאותם אנחנו מכניסים ללינקליסט.  */
        strncat(number, buffer + 0, 20 - 1);
        strncat(full_name, buffer + 21, 20 - 1);
        strncat(id, buffer + 42, 10 - 1);
        strncat(items_purchased, buffer + 53, 20 - 1);
        strncat(enterDate, buffer + 74, 20);


        //In this case we always insert to linked list items that alredy exsist 


        // Check if the line is empty
        if (buffer[0] == '\0')
        {
            continue; // Skip empty line
        }

        printf("\n%-20s %-20s %-20s %-20s %-20s", number, full_name, id, items_purchased, enterDate);
        itemLogger("Display", " a Member", "All", "");
    }
    fclose(file);
}


/*הכנסה של לקוחות לקובץ*/
void handleInsertcustomers()
{

    printf("\nPlease enter Member by inserting the following values followed by space: fullname id \n");
    char  fullname[20] = "", id[10] = "", items_purchased[5] = "0";
    scanf("%s %s", fullname, id);
    if (searchmember(2, id, 0) != NULL) {
        itemLogger("Add", " a Member", "", "Customer with the same ID already exists. Customer was not added.");
        return;
    }
    addNewcustomers(fullname, id, items_purchased);
    itemLogger("Add", " a Member", "", "New Member has been added...");
}


/* we delete member ny member number */
void handleDeletemember()
{
    printf("\nPlease insert a Membernumber :\n");
    char Membernumber[20];
    scanf("%s", Membernumber);
    if (deletecustomers(atoi(Membernumber)))
        itemLogger("delete", "a Member", Membernumber, "Member has been deleted");
    else printf("\nMember has not beed found...\n");
}


//שחרור כלל הרשימה המקושרת של הלקוחות
void releaseMembers()
{
    customers* temp = head;
    Purchase* temp1 = head->purchases_head;
    while (temp != NULL)
    {
        while (temp1 != NULL)
        {
            head->purchases_head = head->purchases_head->next;
            free(temp1);
            temp1 = head->purchases_head;
        }

        head = head->next;
        free(temp);
        temp = head;

    }
}

// Function to delete a customer with a specific member number
int deletecustomers(int memberToDelete)
{
    customers* temp = head;
    customers* prev = NULL;
    if (head != NULL && head->number == memberToDelete) {/*special case when the customer we want to delete is the first one*/
        head = head->next;
        free(temp);
        writecustomersToFile();
        return 1;
    }
    while (temp != NULL && temp->number != (memberToDelete)) {/*cheak if temp.catlog number difrrent from the catlog number from the user*/
        prev = temp;/*if not serch for it in all the link list*/
        temp = temp->next;
    }

    //if the node is last on the list
    if (temp->number == memberToDelete)
    {
        prev->next = temp->next;
        free(temp);
        writecustomersToFile();
        return 1;
    }
    /*if we ended all the list and not find the catlog number we return 0*/
    if (temp == NULL)
        return 0;


}



// Function to remove a customer node with a specific value
void removeMemberWithValue(customers* nodeToRemove)
{
    // Check if the list is empty
    if (head == NULL) {
        printf("The list is empty.\n");
        return;
    }

    customers* Currnode = head;
    customers* prevNode = NULL; // Initialize to NULL as there's no previous node for the head
    customers* Nextnode = head;

    // For the first node in the list
    if (nodeToRemove == head)
    {
        Nextnode = Currnode->next;
        free(Currnode);
        head = Nextnode;
        return; // Return after removing the first node
    }

    // For all nodes between the first and the last
    while (Nextnode->next != NULL) {
        if (Currnode == nodeToRemove) {
            Nextnode = nodeToRemove->next;
            prevNode->next = Nextnode;
            free(Currnode);
            return; // Return after removing the node
        }

        prevNode = Currnode;
        Currnode = Currnode->next;
        Nextnode = Currnode->next;
    }

    // For the last node of the list
    if (Currnode == nodeToRemove) {
        Nextnode = nodeToRemove->next;
        prevNode->next = Nextnode;
        free(Currnode);
    }
}


/* פה אנחנו מדפיסים מידע לקוחות למשתמש, מכניסים קלט ומעדכנים */
void handleUpdatemember()
{
    printf("\nPlease enter the requierd Member to be updated by inserting the following values followed by space:MemberNumber,FullName,Id,items_purchased\n");
    char Membernumber[15] = "", fullname[20] = "", id[15] = "", items_purchased[15] = "";
    scanf("%s %s %s %s", Membernumber, fullname, id, items_purchased);
    if (updatecustomers(Membernumber, fullname, id, items_purchased))
        itemLogger("Update", "Member", "", "Member has been updated");
    else printf("\nWrong ditails, invalid Member...\n");
}


