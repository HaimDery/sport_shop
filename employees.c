#define _CRT_SECURE_NO_WARNINGS


#include "employees.h"
#include"date.h"
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <ctype.h>


//returning the level of the employees
int login()
{
	//getting the info..
	char password[20]="";
	char username[20] = "";
	printf("Welcome to the Sport Shop!\n");
	printf("Please insert your username\n"); 
    scanf("%s",username);
	printf("please insert your password\n");
	scanf("%s",password);

	//checkIfEmployeeFileExists
	char buffer[256] = "";
	FILE* fp = fopen("Employees.txt", "r");

	if (fp == NULL)
	{
		printf("The file dosen't found!");
		fclose(fp);
		return 0;
	}
	else
	{
		while (fgets(buffer, 256, fp)!= NULL)
		{
			char userName[15] ="";
			char passn[15] = "";
			char fullname[21] = "";
			char level[4] = "";
			strncat(userName, buffer, 14);
			strncat(passn, buffer + 16,14);

			if (((0 == strcmp(trimespaces(userName), username)) && (0 == strcmp(trimespaces(passn), password))))
			{
				strncat(fullname, buffer + 36, 20);
				strncat(level, buffer + 31,3);
				itemLogger("Login", "Attempt", "Success", "Login successfully...\n");
				printf("Welcome back %s level %s\n", fullname, level);
				fclose(fp);
				//return the level by his intiger value
				return atoi(level);
			}
			

		}
           //if there isn't any username in the file we return -1.
			printf("Erorr username or password are incorrect! try again \n");
			return -1;
	}
	

}

//telling the pointer to point to the first char in the string that i not a whtiespace.
char* trimespaces(char* str)
{
	char* endptr;
	//in each whitespace(left to right) we increment by 1  the str to the next char place in the memory..
	while (isspace((unsigned char)*str)) 
		str++; 

		if (*str == 0)
			return str;

   // we get endptr to have the addres of the first element that is not whitespace.
	endptr = str + strlen(str) - 1;
	//moving right to left..
	while (endptr > str && isspace((unsigned char)*endptr))
		endptr--;

	//we sign the the next char in the string to be null(end of the new trime string...)
	endptr[1] = '\0';
	return str;
}

//get the defult admin of the system.
void EmployeePreProcessing() 
{
	FILE* file;
	if ((file = fopen("Employees.txt", "r")) != NULL) 
		fclose(file);
	else {
		FILE* file = fopen("Employees.txt", "w");
		if (file == NULL) return;
		fprintf(file, "%-15s %-15s %-3s %-15s", "username", "password", "level", "fullname");
		fprintf(file, "\n%-15s %-15s %-3d %-15s", "admin", "admin", 3, "System_Manager");
		fclose(file);
	}
}
//שחרור רשימה מקושרת של עובדים 
void releaseEmployees()
{
	Employee* temp = NULL;
	while (HeadP != NULL) {
		temp = HeadP;
		HeadP = HeadP->next;
		free(temp);
	}
}

void insertEmployeesToLinkedList()//from text
{
	FILE* fp = fopen("Employees.txt", "r");
	if (fp == NULL)
		return;

	char buffer[256];
	fgets(buffer, sizeof(buffer), fp); // so we won't add the first line in the txt file ("username        password        level fullname..")
	while (fgets(buffer, sizeof(buffer), fp) != NULL)
	{
		char username[20], password[20], level[4], fullname[25];

		sscanf(buffer,"%15s %15s %3s %19s", username, password, level, fullname);

		addNewEmployee(username, password, fullname, level);
	}

	fclose(fp);
}

///*פה אנחנו יוצרים רשימה מקושרת, מעתיקים אליה מהקובץ הכל למעט את העובד שאנחנו לא רוצים למחוק. לאחר שהעתקנו לרשימה המקושרת אנחנו מחזירים בחזרה לקובץ העובדים*/
int deleteEmployee(char employToDelete[20])
{
	// Find the node to remove
	Employee* nodetoremove = FindEmployee(employToDelete);

	if (nodetoremove == NULL)
	{
		printf("Employee doesn't found!");
		return 0;
	}
	else
	{
		// Remove the node from the linked list, לא חייב להשתמש בזה כי כבר בתכלס מצאנו את המשתמש למעלה בשורה הראשונה
		removeNodeWithValue(nodetoremove);

		// Update the file
		FILE* file = fopen("Employees.txt", "w");
		if (file == NULL)
		{
			printf("Error: Could not open the file for writing!\n");
			return 0;
		}

		// Write the header line
		fprintf(file, "%-15s %-15s %-3s %-15s\n", "username", "password", "level", "fullname");

		// Write employee details to the file
		Employee* cur = HeadP;
		while (cur != NULL)
		{
			fprintf(file, "%-15s %-15s %-3d %-15s\n", cur->username, cur->password, cur->level, cur->Full_Name);
			cur = cur->next;
		}
		fclose(file);

		return 1;
	}
}

// A function that receives a pointer to list head and a value.
// The function should find if a node with a given value exists in the list.
// If it does exist, then remove the node from the list and return it.
// Otherwise, return NULL.
void removeNodeWithValue(Employee* nodeToRemove)
{
	// Check if the list is empty
	if (HeadP == NULL) {
		printf("The list is empty.\n");
		return;
	}

	Employee* currNode = HeadP;
	Employee* prevNode = NULL;

	// For the case when the node to remove is the head
	if (nodeToRemove == HeadP) {
		HeadP = HeadP->next;
		free(currNode);
		return;
	}

	// For all nodes other than the head
	while (currNode != NULL) {
		if (currNode == nodeToRemove) {
			prevNode->next = currNode->next;
			free(currNode);
			return;
		}
		prevNode = currNode;
		currNode = currNode->next;
	}

	// If the node is not found
	printf("Node not found in the list.\n");
}

/*כאן אנחנו מציגים את כל המשתמשים. אנחנו פותחים את קובץ המשתמשים ועוברים שורה שורה ומדפיסים*/
void displayEmployees() 
{
	FILE* file = fopen("Employees.txt", "r");
	if (file == NULL) return;
	char buffer[256] = "";
	char username[15] = "", level[4] = "", password[15] = "", fullname[25] = "";
	itemLogger("Display", "Users", "All", "");
	fgets(buffer, 256, file);
	printf("%-15s %-15s %-9s %-15s", "username", "password", "level", "fullname");

	while (fgets(buffer, sizeof(buffer), file) != NULL)
	{
		// Reset variables for each line
		username[0] = '\0';
		password[0] = '\0';
		level[0] = '\0';
		fullname[0] = '\0';
		strncat(username, buffer, 14);
		strncat(password, buffer + 16, 14);
		strncat(level, buffer + 32, 3);
		strncat(fullname, buffer + 36, 15);
		if (fullname[strlen(fullname) - 1] == '\n') {
			fullname[strlen(fullname) - 1] = '\0';
		}
		printf("\n%-15s %-15s %-9s %-15s", username, password, level, fullname);// 15 6
	}
	fclose(file);
}

/*פותחים את קובץ העובדים, ומכניסים את העובד החדש לסוף הרשימה*/
void addEmployee2File(char username[15], char password[15], char level[3], char fullname[25])
{
	FILE* fp = fopen("Employees.txt", "w"); // Open the file in write mode

	if (fp != NULL)
	{
		Employee* cur = HeadP;
		fprintf(fp, "%-15s %-15s %-3s %-25s\n", "username", "password", "level", "fullname"); // Write header

		while (cur != NULL)
		{
			fprintf(fp, "%-15s %-15s %-3d %-25s\n", cur->username, cur->password, cur->level, cur->Full_Name);
			cur = cur->next;
		}

		fclose(fp);
	}
}

// Find a Node within a list with a given value.
// If there's such a node in the list (with the specific value) - return its address.
// Otherwise, return NULL.
Employee* FindEmployee(const char value[20])
{
 	Employee* currentNode = HeadP;
	while (currentNode != NULL)
	{
		if (strcmp(currentNode->username ,value)==0)
			return currentNode;
		currentNode = currentNode->next;
	}
	return NULL;
}

//הוספת עובד לרשימה מקושרת קיימת 
int addNewEmployee(char username[15], char password [15], char fullname[25],char level[3])
{ 
	// Check if the username already exists
	if (FindEmployee(username) != NULL) {
		printf("Username '%s' already exists.\n", username);
		return 0;
	}

	if (fullname[strlen(fullname) - 1] == '\n') {
		fullname[strlen(fullname) - 1] = '\0';
	}
	int levels = level[0] - '0';
	/* יוצרים מצביע למקום בגודל של נוד כאשר נוד זה פריט*/
	Employee* newNode = (Employee*)malloc(sizeof(Employee));
	strcpy(newNode->username,username);
	strcpy(newNode->password,password);
	strcpy(newNode->Full_Name, fullname);
	newNode->level =levels;
	newNode->next = NULL;
	
	
	/* הלינקליסט שלנו מסודר לפי דרגה, מהבכיר מטה. כאשר נכניס נוד חדש נרצה לשמור על הסדר הקיים ולכן נכניס למקום הנכון*/
	if (HeadP == NULL /*|| HeadP->level >= newNode->level*/) {
		HeadP = newNode;
		return 1;
	}
	else 
	{
		Employee* current = HeadP;
		while (current->next != NULL/* && current->next->level <= newNode->level*/)
		{
			if (strcmp(current->username, username) == 0)
			{
				/*printf("username is allready...");*/
				return -1;
			}
			
			current = current->next;
		}
		
		current->next = newNode;
		return 1;
	}
}

void handleAddEmployee()
{

	userAdd = 0;
	printf("\nPlease enter the requierd Employee to add by inserting the following values followed by space: username password level firstname_lastname\n");
	char username[15] = "", password[15] = "", level[3] = "", fullname[25] = "";
	scanf("%s %s %s %s",username,password,level,fullname);
	userAdd = addNewEmployee(username, password, fullname, level);
	addEmployee2File(username, password, level, fullname);
	if (userAdd == 1)
	{
       itemLogger("Add user", "username", username, "\nUser has been added....\n");
	}
	else
		itemLogger("Add user", "username", username, "\nuser has not been added....\n");
		
}

/*מדפיסים למשתמש הודעה שבה מבקשים שם משתמש, מנסים למחוק את שם המשתמש ואם מצליחם מוסיפים אותו מחדש עם הפרטים המעודכנים אם לא מדפיסים הודעת שגיאה*/
void handleUpdateEmployee()
{
	userAdd = 0;
	printf("\nEnter user name to update:\n");
	char toUpdate[15];
	scanf("%s", toUpdate);
	if (deleteEmployee(toUpdate))
	{
		itemLogger("Update user", "username", toUpdate, "\nUser has been founder and going to change....\n");
		printf("\nPlease enter the requierd Employee to add by inserting the following values followed by space: username password level firstname_lastname\n");
		char username[15] = "", password[15] = "", level[3] = "", fullname[25] = "";
		scanf("%s %s %s %s", username, password, level, fullname);
		userAdd = addNewEmployee(username, password, fullname, level);
		addEmployee2File(username, password, level, fullname);
        itemLogger("Add user", "username", username, "\nThe user has been updated successfully....\n");
		
		/*handleAddEmployee();
		printf("The user has been updated successfully");*/
	}
	else printf("\nInvalid username....\n");
}

/* פה אנחנו מדפיסים קלט למשתמש מבקשים ממנו שם משתמש למחוק ומוחקים אותו */
void handleDeleteEmployee()
{
	printf("\nEnter user name to delete:\n");
	char toDelete[15];
	scanf("%s", toDelete);
	if (deleteEmployee(toDelete))
		itemLogger("Delete user", "username", toDelete, "\nUser has been deleted....\n");
	else printf("\nInvalid username....\n");
}