#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

typedef struct
{
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct
{
    Contact contacts[MAX_CONTACTS];
    int contactCount;
} AddressBook;

void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook, int sortCriteria);
void initialize(AddressBook *addressBook);
void saveContactsToFile(AddressBook *AddressBook);

// validate funtions
int name_validate(char *);
int phone_validate(char *);
int phone_dup(AddressBook *, char *);
int mail_validate(char *);
int email_dup(AddressBook *, char *);

// search funtions
int search_name(char *, AddressBook *);
int search_phone(char *, AddressBook *);
int search_email(char *, AddressBook *);

// edit funtions
void what_edit(AddressBook *, int);
int edit_contact(int, AddressBook *, int);
int search_by_name(char *, AddressBook *);
int search_by_phone(char *, AddressBook *);
int search_by_email(char *, AddressBook *);

// delete funtions
void delete_conf(int, AddressBook *);
int conf_validate(char);

// print funtions
void print_head();
void print_contact(int, AddressBook *);
#endif
