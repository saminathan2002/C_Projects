#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0;
    // populateAddressBook(addressBook);

    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook)
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS);              // Exit the program
}

// Funtion to Create a new contact
void createContact(AddressBook *addressBook)
{
    char name[20];
    char phone[10];
    char email[100];
    printf("\n--- Create a New Contact ---\n");
    int i = 0, j = 0;
    do
    {
        printf("Enter the full Name: ");
        scanf(" %[^\n]", name);
        i = name_validate(name); // call a funtion to validate input name
    } while (i == 0);
    strcpy(addressBook->contacts[addressBook->contactCount].name, name); // store validated name in array of structure

    do
    {
        printf("Enter the phone Number: ");
        scanf(" %[^\n]", phone);
        i = phone_validate(phone);         // call a funtion to validate input phone number
        j = phone_dup(addressBook, phone); // call a function to check if an phone number present in the database
    } while (i == 0 || j == 0);
    strcpy(addressBook->contacts[addressBook->contactCount].phone, phone); // store phone number in array of structure

    do
    {
        printf("Enter the email Address: ");
        scanf(" %[^\n]", email);
        i = mail_validate(email);          // call a funtion to validate input email address
        j = email_dup(addressBook, email); // call a function to check if an email already present in the database
    } while (i == 0 || j == 0);

    strcpy(addressBook->contacts[addressBook->contactCount].email, email); // store validated email address in array of structure
    addressBook->contacts[addressBook->contactCount++];                    // Increment contactCount for the next contact
    printf("Contact saved successfully! Returning to the main menu...\n");
}

// Function to search for a contact
void searchContact(AddressBook *addressBook)
{
    int search;
    printf("\n--- Search for a Contact ---\n1.Search by Name\n2.Search by Phone number\n3.Search by Email Address\nEnter your choice: ");
    scanf("%d", &search);
    switch (search)
    {
    case 1:
    {
        char name[20];
        int i = 0;
        do
        {
            printf("Enter the name to search: ");
            scanf(" %[^\n]", name);
            i = name_validate(name); // call a funtion to validate input name
        } while (i == 0);

        search_name(name, addressBook); // call the function to search the contact by name
    }
    break;
    case 2:
    {
        char phone[20];
        int i;
        do
        {
            printf("Enter the phone number to search: ");
            scanf(" %[^\n]", phone);
            i = phone_validate(phone); // call a funtion to validate input phone number
        } while (i == 0);

        search_phone(phone, addressBook); // call the function to search the contact by phone number
    }
    break;
    case 3:
    {
        char email[20];
        int i = 0;
        do
        {
            printf("Enter the email address to search: ");
            scanf(" %[^\n]", email);
            i = mail_validate(email); // call a funtion to validate input email address
        } while (i == 0);

        search_email(email, addressBook); // call the function to search the contact by email address
    }
    break;
    }
}

// Function to edit a contact's details
void editContact(AddressBook *addressBook)
{
    printf("\n--- Edit Contact Details ---\n");
    int search;
    printf("How would you like to search for the contact?\n1.Search by name\n2.Search by phone number\n3.Search by email address\nEnter your choice: ");
    scanf("%d", &search);
    switch (search)
    {
    case 1:
    {
        char s_name[20];
        int i = 0;
        do
        {
            printf("Enter the name you want to search for: ");
            scanf(" %[^\n]", s_name);
            i = name_validate(s_name); // call a funtion to validate input name
        } while (i == 0);

        int ind = search_by_name(s_name, addressBook); // call the function to search the contact by name

        if (ind >= 0)
        {
            printf("\nContact found! Here are the current details:\n");
            what_edit(addressBook, ind); // Call the function to edit the found contact
        }
        else
        {
            printf("\nSorry, no contact found!\n");
        }
    }
    break;
    case 2:
    {
        char s_phone[20];
        int i;
        do
        {
            printf("Enter the phone number you want to search for: ");
            scanf(" %[^\n]", s_phone);
            i = phone_validate(s_phone); // call a funtion to validate input phone number
        } while (i == 0);

        int ind = search_by_phone(s_phone, addressBook); // call the function to search the contact by phone number

        if (ind >= 0)
        {
            printf("\nContact found! Here are the current details:\n");
            what_edit(addressBook, ind); // Call the function to edit the found contact
        }
        else
        {
            printf("\nSorry, no contact found!\n");
        }
    }
    break;
    case 3:
    {
        char s_email[20];
        int i = 0;
        do
        {
            printf("Enter the email address you want to search for: ");
            scanf(" %[^\n]", s_email);
            i = mail_validate(s_email); // call a funtion to validate input email address
        } while (i == 0);

        int ind = search_by_email(s_email, addressBook); // call the function to search the contact by email address

        if (ind >= 0)
        {
            printf("\nContact found! Here are the current details:\n");
            what_edit(addressBook, ind); // Call the function to edit the found contact
        }
        else
        {
            printf("\nSorry, no contact found!\n");
        }
    }
    break;
    }
}

// Function to delete a contact
void deleteContact(AddressBook *addressBook)
{
    printf("\n--- Delete a Contact ---\n");
    int search, i = 0;
    printf("\n");
    printf("How would you like to search for the contact?\n1.Search by Name\n2.Search by Phone number\n3.Search by Email address\nEnter your choice: ");
    scanf("%d", &search);
    switch (search)
    {
    case 1:
    {
        char s_name[20];
        int i = 0;
        do
        {
            printf("Enter the name to search: ");
            scanf(" %[^\n]", s_name);
            i = name_validate(s_name);
        } while (i == 0);

        int ind = search_by_name(s_name, addressBook);
        if (ind >= 0)
        {
            printf("Contact found!!!\n");
            print_contact(ind, addressBook);
            printf("\n");
            delete_conf(ind, addressBook);
        }
        else
        {
            printf("Sorry, contact not found");
        }
    }
    break;
    case 2:
    {
        char s_phone[20];
        int i;
        do
        {
            printf("Enter the phone number to search:");
            scanf(" %[^\n]", s_phone);
            i = phone_validate(s_phone);
        } while (i == 0);

        int ind = search_by_phone(s_phone, addressBook);

        if (ind >= 0)
        {
            printf("Contact found!!!\n");
            print_contact(ind, addressBook);
            delete_conf(ind, addressBook);
        }
        else
        {
            printf("Sorry! Contact not found!!!\n");
        }
    }
    break;
    case 3:
    {
        char s_email[20];
        int i = 0;
        do
        {
            printf("Enter the email address to search:");
            scanf(" %[^\n]", s_email);
            i = mail_validate(s_email);
        } while (i == 0);

        int ind = search_by_email(s_email, addressBook);
        if (ind >= 0)
        {
            printf("Contact found!!!\n");
            print_contact(ind, addressBook);
            delete_conf(ind, addressBook);
        }
        else
        {
            printf("Sorry, contact not found!!!\n");
        }
    }
    break;
    }
}
// Function to list a contact's details
void listContacts(AddressBook *addressBook, int sortCriteria)
{
    int res;
    for (int i = 0; i < addressBook->contactCount - 1; i++)
    {
        for (int j = 0; j < addressBook->contactCount - 1 - i; j++)
        {
            switch (sortCriteria)
            {
            case 1:
                res = strcmp(addressBook->contacts[j].name, addressBook->contacts[j + 1].name);
                break;
            case 2:
                res = strcmp(addressBook->contacts[j].phone, addressBook->contacts[j + 1].phone);
                break;
            case 3:
                res = strcmp(addressBook->contacts[j].email, addressBook->contacts[j + 1].email);
                break;
            }

            if (res > 0)
            {
                Contact temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j + 1];
                addressBook->contacts[j + 1] = temp;
            }
        }
    }
    printf("\n");
    print_head();
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        printf("%-5d %-20s %-15s %-15s\n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }
}

// ================================== FUNCTIONS ============================================
// Function to validate if the input name contains only letters and spaces
int name_validate(char *name)
{
    while (*name)
    {
        // check for valid characters
        if (!(*name >= 'A' && *name <= 'Z' || *name >= 'a' && *name <= 'z' || *name == ' '))
        {
            printf("Invalid name detected! Name containing only letters.\n");
            return 0; // exit with error statement
        }
        name++; // move to next character in string
    }
    return 1; // Return success if valid name
}

// Function to validate if the input phone number contains only digits
int phone_validate(char *phn)
{
    // check only 10 digit numbers
    if (strlen(phn) != 10)
    {
        printf("Please enter a valid 10-digit phone number.\n");
        return 0; // exit with error statement
    }
    while (*phn)
    {
        // check for validate number
        if (!(*phn >= '0' && *phn <= '9'))
        {
            printf("Invalid phone number detected! Phone number containing only numbers.\n");
            return 0; // exit with error statement
        }
        phn++; // move to next character in string
    }
    return 1; // Return success if valid phone number
}

// Function to check if an phone number already present in the database
int phone_dup(AddressBook *addressBook, char *phone)
{
    int res;
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        // check in database
        res = strcmp(addressBook->contacts[i].phone, phone);
        if (res == 0)
        {
            printf("Error! This number is already saved.\n");
            return 0; // if duplicate found, exit
        }
    }
    return 1; // Return success if valid phone number
}

// Function to validate input email address
int mail_validate(char *mail)
{
    int count = 0;
    char *position = NULL;

    // email doesn't start with '@' or a number
    if (*mail == '@' || *mail >= '0' && *mail <= '9')
    {
        printf("\nError: Email cannot start with '@' or a number.\n");
        return 0; // not valid, exit with error statement
    }

    for (char *p = mail; *p != '\0'; p++)
    {
        // check for valid characters
        if (*p >= 'a' && *p <= 'z' || *p >= '0' && *p <= '9' || *p == '.' || *p == '@' || *p == '_')
        {
            if (*p == '@')
            {
                count++;
                if (count == 1)
                {
                    position = p; // position of '@'
                }
                if (count > 1)
                {
                    printf("\nError: Email cannot contain more than one '@'\n\n");
                    return 0; // if not valid, exit with error statement
                }
            }
        }
        else
        {
            printf("\nError: Invalid character in email.\n\n");
            return 0; // if not valid, exit with error statement
        }
    }

    // check if '@' is present and not at the start or end
    if (count != 1)
    {
        printf("\nError: Missing or invalid '@' in email\n\n");
        return 0; // if not valid, exit with error statement
    }

    // check there is a domain after '@'
    char *domain = position + 1;
    if (*domain == '\0')
    {
        printf("\nError: Missing domain name after '@'\n\n");
        return 0; // if not valid, exit with error statement
    }

    // check domain does not start with '.'
    if (*domain == '.')
    {
        printf("\nError: Domain name cannot start with '.'\n\n");
        return 0; // if not valid, exit with error statement
    }

    // check for '.com' at the end
    if (!strstr(domain, ".com"))
    {
        printf("\nError: Missing '.com' in the domain name.\n");
        return 0; // if not valid, exit with error statement
    }
    return 1; // Return success if valid email address
}

// Function to check if an email already present in the database
int email_dup(AddressBook *addressBook, char *email)
{
    int res;
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        // check in database
        res = strcmp(addressBook->contacts[i].email, email);
        if (res == 0)
        {
            printf("Error: This email is already saved!\n");
            return 0; // if duplicate found, exit
        }
    }
    return 1; // Return success if no duplicate found
}

// Search Contact
// Function to search for a contact by name
int search_name(char *name, AddressBook *addressBook)
{
    int find = 0;
    int found = 0; // Flag to ensure "Contact found!" is printed only once
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcasestr(addressBook->contacts[i].name, name)) // Check if the name found in database
        {
            if (!found)
            {
                find = 1;
                found = 1;
                printf("\nContact found!\n");
            }
            printf("%-20s %-15s %-15s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
        }
    }
    if (find == 0)
    {
        printf("\nSorry, no contact found!\n");
        return 0;
    }
}

// Function to search for a contact by phone number
int search_phone(char *phone, AddressBook *addressBook)
{
    int find = 0;
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strstr(addressBook->contacts[i].phone, phone)) // Check if the phone number found in database
        {
            find = 1;
            printf("\nContact found!\n");
            printf("%-20s %-15s %-15s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
        }
    }
    if (find == 0)
    {
        printf("\nSorry, no contact found!\n");
        return 0;
    }
}

// Function to search for a contact by email address
int search_email(char *email, AddressBook *addressBook)
{
    int find = 0;
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcasestr(addressBook->contacts[i].email, email)) // Check if the email address found in database
        {
            find = 1;
            printf("\nContact found!\n");
            printf("%-20s %-15s %-15s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
        }
    }
    if (find == 0)
    {
        printf("\nSorry, no contact found!\n");
        return 0;
    }
}

// Search contact (Specifically for editing contacts)
// Function to search for a contact by name for edit contact
int search_by_name(char *name, AddressBook *addressBook)
{
    int count = 0, i, ind;
    for (i = 0; i < addressBook->contactCount; i++)
    {
        if (strcasestr(addressBook->contacts[i].name, name)) // Check if the name found in database
        {
            count++;
            ind = i;
        }
    }
    // Single contact found case
    if (count == 1)
    {
        return ind; // Return the index of the single contact
    }
    // Multiple contact found cases
    else if (count > 1)
    {
        printf("\nMultiple contacts found with the name!\n1. Search by Phone Number\n2. Search by Email Address\nEnter your choice: ");
        int found;
        scanf("%d", &found);
        switch (found)
        {
        case 1:
        {
            char phone[20];
            int i;
            do
            {
                printf("Enter the phone number to search: ");
                scanf(" %[^\n]", phone);
                i = phone_validate(phone); // call a funtion to validate input phone number
            } while (i == 0);
            int res = search_by_phone(phone, addressBook); // call the function to search the contact by phone number
            return res;
        }
        break;
        case 2:
        {
            char email[20];
            int i = 0;
            do
            {
                printf("Enter the email address to search: ");
                scanf(" %[^\n]", email);
                i = mail_validate(email); // call a funtion to validate input email address
            } while (i == 0);
            int res = search_by_email(email, addressBook); // call the function to search the contact by email address
            return res;
        }
        }
    }
    else if (count == 0)
    {
        return -1;
    }
}

// Function to search for a contact by phone number for edit contact
int search_by_phone(char *phone, AddressBook *addressBook)
{
    int find = -1, count = 0, i, ind;
    for (i = 0; i < addressBook->contactCount; i++)
    {
        if (strcasestr(addressBook->contacts[i].phone, phone)) // Check if the phone number found in database
        {
            find = 1;
            count++;
            ind = i;
        }
    }
    if (count == 1)
    {
        return ind; // Return the index of the contact
    }
    if (find == -1)
    {
        return -1;
    }
}

// Function to search for a contact by email address for edit contact
int search_by_email(char *email, AddressBook *addressBook)
{
    int find = -1, count = 0, i, ind;
    for (i = 0; i < addressBook->contactCount; i++)
    {
        if (strcasestr(addressBook->contacts[i].email, email)) // Check if the email address found in database
        {
            find = 1;
            count++;
            ind = i;
        }
    }
    if (count == 1)
    {
        return ind; // Return the index of the contact
    }
    if (find == -1)
    {
        return -1;
    }
}

// Function to updated contact
int edit_contact(int found, AddressBook *addressBook, int ind)
{
    switch ((found))
    {
    case 1:
        char edit_name[20];
        int i = 0, j = 0;
        do
        {
            printf("Enter the new Name: ");
            scanf(" %[^\n]", edit_name);
            i = name_validate(edit_name); // call a funtion to validate input name
        } while (i == 0);
        strcpy(addressBook->contacts[ind].name, edit_name); // store updated validated name in structure
        break;
    case 2:
        char edit_phone[20];
        do
        {
            printf("Enter the new Phone Number: ");
            scanf(" %[^\n]", edit_phone);
            i = phone_validate(edit_phone);         // call a funtion to validate input phone number
            j = phone_dup(addressBook, edit_phone); // call a function to check if an phone number present in the database
        } while (i == 0 || j == 0);
        strcpy(addressBook->contacts[ind].phone, edit_phone); // store updated validated phine number in structure
        break;
    case 3:
        char edit_mail[20];
        do
        {
            printf("Enter the new email address: ");
            scanf(" %[^\n]", edit_mail);
            i = mail_validate(edit_mail);          // call a funtion to validate input email address
            j = email_dup(addressBook, edit_mail); // call a function to check if an email already present in the database
        } while (i == 0 || j == 0);
        strcpy(addressBook->contacts[ind].email, edit_mail); // store updated validated email address in structure
        break;
    }
}

void what_edit(AddressBook *addressBook, int ind)
{
    print_contact(ind, addressBook);
    printf("\nWhat detail would you like to update?\n1.Name\n2.Phone number\n3.Email address\nEnter your choice: ");
    int found;
    scanf("%d", &found);
    edit_contact(found, addressBook, ind);
    printf("\nDetails updated successfully! Here are the updated details!\n");
    print_contact(ind, addressBook);
}

// DELETE
// yes or no validate
int conf_validate(char conf)
{
    if (conf == 'n' || conf == 'N' || conf == 'y' || conf == 'Y')
    {
        return 1;
    }
    else
    {
        printf("Enter only Y/N\n");
        return 0;
    }
}
// delete conformation
void delete_conf(int ind, AddressBook *addressBook)
{
    char conf;
    int i;
    do
    {
        printf("Do you want delete this contact (Y/N)\n");
        scanf(" %c", &conf);
        i = conf_validate(conf);
    } while (i == 0);
    if (conf == 'y' || conf == 'Y')
    {
        for (int i = ind; i < addressBook->contactCount; i++)
        {
            addressBook->contacts[i] = addressBook->contacts[i + 1];
        }
        addressBook->contactCount--;
        printf("\nContact deleted successfully!\n");
    }
    else if (conf == 'n' || conf == 'N')
    {
        printf("\nContact not deleted!\n");
    }
}
// print
void print_head()
{
    printf("----------------------------------------------------------------\n");
    printf("%-5s %-20s %-15s %-15s\n", "S.No", "Name", "Phone number", "Email ID");
    printf("----------------------------------------------------------------\n");
}
void print_contact(int ind, AddressBook *addressBook)
{
    printf("%-20s %-15s %-15s\n", addressBook->contacts[ind].name, addressBook->contacts[ind].phone, addressBook->contacts[ind].email);
}