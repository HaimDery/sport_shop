#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h> 
#include <string.h>
#include "items1.h"
#include "customers.h"
#include "Purchases.h"
#include "date.h"
#include <time.h>


/*write from the linked list after update purchase*/
void WritePurchasesToFile() {
    customers* temp = head;
    FILE* fp = fopen("purchases.txt", "w");
    if (fp == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    fprintf(fp,"%-20s %-20s %-20s %-20s %-20s %-20s\n", "Recipt_Number", "Client number", "Catalog number", "Quantity","price", "Date");

    while (temp != NULL) {
        Purchase* purchase = temp->purchases_head;
        while (purchase != NULL) {
            fprintf(fp, "%-20d %-20d %-20d %-20d %-20f %02d/%02d/%d\n",
                purchase->Recipt_Number, purchase->Client_num,
                purchase->catlog_Number, purchase->quantity, purchase->price,
                purchase->purchase_date.dd, purchase->purchase_date.mm, purchase->purchase_date.yyyy);
            purchase = purchase->next;
        }
        temp = temp->next;
    }

    fclose(fp);
    return;
}



/*insert new purchase */
void handleInsertPurchase()
{
    printf("\nPlease enter purchase details (number of clients,catlog number,Quantity):\n ");
    char Recipt_Number[20] = "3", Client_num[20] = "",catlog_Number[20] = "", quantity[20] = "";

    scanf("%s %s %s",Client_num,catlog_Number,quantity);
    if (atoi(quantity) > 3) {
        printf("quntity too high...only 3 pieces in one buying.");
            return;
    }
    addNewPurchase(Recipt_Number, Client_num, catlog_Number, quantity);
    itemLogger("Add", "client number", Client_num, "New purchase has been added...");
}


//Adding new item(to the linkedlist & text file)see if change char to int
void addNewPurchase(char Recipt_Number[20], char client_num[20],char catalog_num[20],char quantity[20])
{
    float price = find_price(atoi(catalog_num),atoi(quantity));
    //הוספת המידע לרשימה מקושרת
    addNewNodeToPurchaseList(1, atoi(Recipt_Number),atoi(client_num),atoi(catalog_num),atoi(quantity),price,"geting date");
}





//This function update the linked list of every customer in the shop.
//The flag is for knowing if the customers already exists(just update data) or we need to create for him new node
void addNewNodeToPurchaseList(int flag, int Recipt_Number, int client_num, int catlog_Number, int quantity,float price, char enterdate[20]) {
    // Find the customer in the list
    customers* customer = findCustomer(client_num);
    int TempRecipt = 2;
    if (customer == NULL) 
    {
        printf("Customer not found.\n");
        return;
    }

    // Allocate memory for new purchase node
    Purchase* new_purchase = (Purchase*)malloc(sizeof(Purchase));
    if (new_purchase == NULL) 
    {
        printf("Error: Memory allocation failed for new purchase node.\n");
        return;
    }

    // Fill in the purchase details
    new_purchase->Recipt_Number = Recipt_Number;
    new_purchase->Client_num = client_num;
    new_purchase->catlog_Number = catlog_Number;
    new_purchase->quantity = quantity;
    new_purchase->next = NULL;
    new_purchase->price = price;

    //flag = 1  it's new purchase.we update the file.
    if (flag == 1) 
    {
        // If the customer has no previous purchases, set the new purchase as the first
        if (customer->purchases_head == NULL) {
            updateInventory(new_purchase->catlog_Number,new_purchase->quantity,0);/*also upadate the item invntory*/
            getDateTime(&new_purchase->purchase_date);
            customer->purchases_head = new_purchase;
            customer->purchases_head->Recipt_Number = 1;
            customer->items_purchased = quantity;
            writecustomersToFile();
            addToPurchaseFile(new_purchase);
        }
        else {
            updateInventory(new_purchase->catlog_Number,new_purchase->quantity,0);/*update the item invntory*/
            getDateTime(&new_purchase->purchase_date);
            customer->items_purchased = customer->items_purchased + quantity;
            writecustomersToFile();

            // Find the end of the customer's list of purchases
            Purchase* current = customer->purchases_head;
            while (current->next != NULL) 
            {
                
                    TempRecipt++;
                

                current = current->next;
                
            }
            // Append the new purchase to the end of the list
            new_purchase->Recipt_Number= TempRecipt; 
            current->next = new_purchase;
           // Add this purchase to the "purchases.txt" file
            addToPurchaseFile(new_purchase);
        }
       

      
    }
    //If it's an update from file, set the new purchase as the head of the list.
    else       //flag=0
    {         //get the date into the node.
             //getting the original date from the file
       
        sscanf(enterdate,"%d/%d/%d",&(new_purchase->purchase_date.dd),&(new_purchase->purchase_date.mm),&(new_purchase->purchase_date.yyyy));
        if (customer->purchases_head == NULL)/*chack if the head is null.if not we skip on that if.*/
        {
            customer->purchases_head = new_purchase;
            new_purchase->next = NULL;
        }
        else 
        {
            Purchase* TEMP = customer->purchases_head;
            while (TEMP->next != NULL && TEMP->next->Recipt_Number < new_purchase->Recipt_Number)
            {
                TEMP = TEMP->next;
            }
            new_purchase->next = TEMP->next;
            TEMP->next = new_purchase;
        }
    }
 }
        
       
  

//find customer from the customer list
 customers* findCustomer(int x)
 {
    customers* current = head;
    while (current != NULL) {
        if (current->number == x) {
            return current; // Customer found
        }
        current = current->next;
    }
    return NULL; // Customer not found
}


 /*insert data from the file to linked list*/
void insertPurchasesToList()
{
    FILE* fp = fopen("purchases.txt", "r");
    if (fp == NULL) return;

    char buffer[256] = "";
    fgets(buffer, 256, fp);  // Read and discard the header line

    while (fgets(buffer, 256, fp) != NULL) {
        char Recipt_Number[20]="", client_num[20]="", catalog_num[20]="", quantity[20]="",price[20]="", enterDate[20] = "";
        strncat(Recipt_Number, buffer + 0, 19);
        strncat(client_num, buffer + 21, 19);
        strncat(catalog_num, buffer + 42, 19);
        strncat(quantity, buffer + 63, 19);
        strncat(price, buffer + 84, 19);
        strncat(enterDate, buffer + 105, 19);
      
     
        
        addNewNodeToPurchaseList(0, atoi(Recipt_Number), atoi(client_num), atoi(catalog_num), atoi(quantity),atof(price), enterDate);
    }

    fclose(fp);
}






//function that take data from the node that created and update the file
void addToPurchaseFile(Purchase* newnode)
{
    FILE* fp = fopen("purchases.txt","a+");
    time_t t = time(NULL);
    struct tm* tm_info = localtime(&t);
    char dateFormatted[20];

    if (fp == NULL) {
        printf("Cannot open the file!\n");
        return;
    }
    if (dateFormatted[strlen(dateFormatted) - 1] == '\n') {
        dateFormatted[strlen(dateFormatted) - 1] = '\0';
    }

    //Format the date to "dd/mm/yyyy"
    strftime(dateFormatted,sizeof(dateFormatted),"%d/%m/%Y",tm_info);
  

            fprintf(fp,"\n%-20d %-20d %-20d %-20d %-20.3f %-20s", newnode->Recipt_Number,newnode->Client_num, newnode->catlog_Number, newnode->quantity, newnode->price,dateFormatted);
            fclose(fp);
      
    }


//disply all the purchase
void displaypurchase() {
    FILE* file = fopen("purchases.txt", "r");
    if (file == NULL) return;
    char buffer[256] = "";
    char header[256];
    fgets(header, sizeof(header), file);
    printf("\n%-20s %-20s %-20s %-20s %-20s %-20s", "Recipt_Number", "Client number", "Catalog number", "Quantity", "price", "Date");
    while (fgets(buffer, 256, file) != NULL) {
        char Recipt_Number[20] = "", client_num[20] = "", catalog_num[20] = "", quantity[20] = "",price[20]= "", enterDate[20] = "";
        strncat(Recipt_Number, buffer + 0,19);
        strncat(client_num, buffer + 21,19);
        strncat(catalog_num, buffer + 42,19);
        strncat(quantity, buffer + 63,19);
        strncat(price, buffer + 84, 19);
        strncat(enterDate, buffer + 100,19);

        // Check if the line is empty
        if (buffer[0] == '\0')
        {
            continue; // Skip empty line
        }

        printf("\n%-20s %-20s %-20s %-20s %-20s %-20s", Recipt_Number, client_num, catalog_num, quantity,price, enterDate);
        itemLogger("Display", "purchase", "All", "");
    }
    fclose(file);
}

//chack if  we want to display by customer number or all the purchase
void handledisplaypurchases() {
    int choice;
    

    printf("enter your choice : \n1.all purchases\n2.purchases by client number\n");
    scanf("%d", &choice);
    if (choice == 1) {
        displaypurchase();
    }
    else {
        char choosen_client_num[20];
        printf("enter client number:\n");
        scanf("%20s", choosen_client_num);
        FILE* file = fopen("purchases.txt", "r");
        if (file == NULL) return;
        
        char buffer[256] = "";
        printf("%-20s %-20s %-20s %-20s %-20s %-20s\n", "Recipt_Number", "Client number", "Catalog number", "Quantity", "price", "Date");
        while (fgets(buffer, 256, file) != NULL) {
            char Recipt_Number[20] = "", client_num[20] = "", catalog_num[20] = "", quantity[20] = "", price[20] = "", enterDate[20] = "";
            strncat(Recipt_Number, buffer + 0, 19);
            strncat(client_num, buffer + 21, 19);
            strncat(catalog_num, buffer + 42, 19);
            strncat(quantity, buffer + 63, 19);
            strncat(price, buffer + 84, 19);
            strncat(enterDate, buffer + 105, 19);

            // Check if the line is empty
            if (buffer[0] == '\0')
            {
                continue; // Skip empty line
            }
            if (strcmp(trimespaces(client_num), choosen_client_num) == 0) {
                printf("\n%-20s %-20s %-20s %-20s %-20s %-20s", Recipt_Number, client_num, catalog_num, quantity,price, enterDate);
                  itemLogger("Display", "purchase", "by customer number ", "");
            }
        }
        fclose(file);
    }

    
}

void HandleReturns()
{

    int CatalogNum, return1, ReciptNum, ClientNum,NumOfReturns ;
    printf("Returning item protocol:\n");
    printf("insert recipt number and client number:\n");

    scanf("%d %d", &ReciptNum, &ClientNum);/*get from the employee the details*/
    //search for the exact client.
    customers* Customer = findCustomer(ClientNum);
    if (Customer != NULL) {
        //checking if the purchase date didnt pass 14 days&remove node from the L.L
        return1 = Returns14(ClientNum, ReciptNum, Customer, &NumOfReturns, &CatalogNum);

        if (return1 == 1)
        {
            WritePurchasesToFile();
            //update invetory.
            updateInventory(CatalogNum, NumOfReturns, 1);
            Customer->items_purchased = Customer->items_purchased - NumOfReturns;/*DECRESE THE NUMBER OF CUSTOMER ITEMS PURCHASES*/
            writecustomersToFile();
            WriteItemsToFile();
            //write the operation to the log file
            char str[4];
            //convert the decimal num to string.
            _itoa(CatalogNum, str, 10);
            itemLogger("Return", "Items no", str, "Item has been Return...");
            return;
        }
    }
    else
        printf("customer doesn't found!\n");
        return;
}

  //getting the head of the list and make the return.
//report if the return was complited.
  int Returns14(int ClientNum, int Recipt_Number,struct customers* Customer,int*quantity,int*CatalogNum)
  {
      //getting the real time
      time_t currentTime = time(NULL);
      struct tm* currentDate = localtime(&currentTime);
      //לבדוק העברה של הנוד הספציפי במקום חיפוש כפול
      Purchase* currentPurchase = Customer->purchases_head;
      Purchase* previousPurchase = NULL;
      //finding the the node inside the purchases list
      if (Customer != NULL)
      {

          while (currentPurchase != NULL) {


              //If we found the client list
              // If 14 days hasn't passed since the purchase
              if (currentPurchase->Client_num == ClientNum && currentPurchase->Recipt_Number ==Recipt_Number )
              {
                  *quantity = currentPurchase->quantity;
                  *CatalogNum = currentPurchase->catlog_Number;
                  // Calculate the time elapsed since the purchase
                 //mktime transfer the date to time_t format. 
                  struct tm tm_date = dateToTm(currentPurchase->purchase_date);
                  time_t purchaseTime = mktime(&tm_date);
                  //gett the time diferences
                /*  double x = &currentTime;
                  double y = &purchaseTime;*/
                  double timeDifference = (currentTime) - (purchaseTime);
                  // Convert seconds to days
                  double daysDifference = timeDifference/(60 * 60 * 24);
                  //make the "return" by removing the node  
                  if (daysDifference <= 14)
                  {

                      if (previousPurchase == NULL)
                      {//meaning its the first node
                          previousPurchase = currentPurchase;
                          currentPurchase = currentPurchase->next;
                          free(previousPurchase); // Free memory if removing the purchase
                          Customer->purchases_head = currentPurchase;//up dating the head list
                      }
                      else
                      {
                          previousPurchase->next = currentPurchase->next;
                          free(currentPurchase); // Free memory if removing the purchase
                      }

                      return 1;
                  }

              }
              else// Move to the next purchase
              

                  previousPurchase = currentPurchase;
                  currentPurchase = currentPurchase->next;
              
          }
          printf("The deal is not refundable!\n");
          return 0;
      }
      printf("The customer doesn't found!\n");
      return 0;
  }

  /*found how much the items cost*/
  float find_price(int catlog_num,int quntity) {
      item* temp=HeadPtr;
      int num_price;
      while (temp->Catlog_Number != catlog_num) {
          temp = temp->next;
      }
      if (quntity = 2) {
          num_price = (temp->price) * 2;
          return(num_price);
      }
      else if (quntity = 3) {
          num_price = (temp->price) * 3;
          return(num_price);
      }
      else return(temp->price);
  }

