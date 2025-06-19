/* 
Name: Saminathan S
Date: 15-04-2025
Description: An Address Book program to manage and store contact information
Features:
1. Create a new contact (Name, Phone Number, Email Address)
2. Search for an existing contacts by Name, Phone Number, or Email Address
3. Edit a contact's details
4. Delete a contact
5. Display all contacts
6. Saving and Exiting..

Sample Input:
====== Welcome to the Address Book ======
1. Create a new contact
2. Search for an existing contact
3. Edit a contact's details
4. Delete a contact
5. List all saved contacts
6. Exit
Enter your choice: 1

--- Create a New Contact ---
Enter the full Name: John Doe
Enter the phone Number: 1234567890
Enter the email Address: john.doe@example.com"

Sample Output:
Contact saved successfully! Returning to the main menu...
*/

#include <stdio.h>
#include "contact.h"

int main()
{
    int choice;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book

    do
    {
        printf("\n====== Welcome to the Address Book ======\n");
        printf("1. Create a new contact\n");
        printf("2. Search for an existing contact\n");
        printf("3. Edit a contact's details\n");
        printf("4. Delete a contact\n");
        printf("5. List all saved contacts\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();
        switch (choice)
        {
        case 1:
            createContact(&addressBook);
            break;
        case 2:
            searchContact(&addressBook);
            break;
        case 3:
            editContact(&addressBook);
            break;
        case 4:
            deleteContact(&addressBook);
            break;
        case 5:
            printf("\n--- List All Saved Contacts ---\n");
            printf("Select sort criteria:\n");
            printf("1.Sort by name\n");
            printf("2.Sort by phone number\n");
            printf("3.Sort by email address\n");
            printf("Enter your choice: ");
            int sortChoice;
            scanf("%d", &sortChoice);
            listContacts(&addressBook, sortChoice);
            break;
        case 6:
            printf("Saving and Exiting...\n");
            saveContactsToFile(&addressBook);
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);
    return 0;
}
