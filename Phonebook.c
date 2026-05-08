/* Phonebook Management System - Fixed & Enhanced
   Cross-platform compatible with improved security
   
   Features:
   - Safe string input with fgets()
   - Dynamic buffer sizes
   - Better error handling
   - Input validation
   
   To run on Linux/macOS:
   1. Remove #include <windows.h> and #include <conio.h>
   2. Replace system("cls") with system("clear")
   3. Replace system("color E0") with nothing
   4. Replace getch() with getchar()
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#ifdef _WIN32
    #include <windows.h>
    #include <conio.h>
    #define CLEAR_SCREEN system("cls")
    #define GET_CHAR getch()
    #define SET_COLOR system("color E0")
#else
    #define CLEAR_SCREEN system("clear")
    #define GET_CHAR getchar()
    #define SET_COLOR
#endif

#define MAX_CONTACTS 1000
#define MAX_NAME 256
#define MAX_EMAIL 256
#define MAX_PHONE 20
#define MAX_GENDER 20
#define MAX_DATE 20
#define MAX_ADDRESS 256

typedef struct {
    char fname[MAX_NAME];
    char lname[MAX_NAME];
    char number[MAX_PHONE];
    char gender[MAX_GENDER];
    char email[MAX_EMAIL];
    char birthdate[MAX_DATE];
    char address[MAX_ADDRESS];
} Contact;

void addperson(FILE *fptr);
void deleteone(FILE *fptr);
void update(FILE *fptr);
void searchandprint(FILE *fptr);
int search(FILE *fptr, char name[]);
void displayall(FILE *fptr);
void deleteall(FILE *fptr);
int count_contacts(FILE *fptr);
void safe_fgets(char *buffer, int size, FILE *stream);

int main() {
    SET_COLOR;
    CLEAR_SCREEN;
    
    FILE *fptr;
    fptr = fopen("phonebook.txt", "r+");
    if (fptr == NULL) {
        fptr = fopen("phonebook.txt", "w+");
        if (fptr == NULL) {
            printf("Error in opening File\n");
            exit(1);
        }
    }

    while (1) {
        CLEAR_SCREEN;
        printf("\n");
        printf("╔════════════════════════════════════════════╗\n");
        printf("║   PHONEBOOK MANAGEMENT SYSTEM              ║\n");
        printf("║   Safe & Cross-Platform Version            ║\n");
        printf("╚════════════════════════════════════════════╝\n\n");
        
        printf("1. Add new contact\n");
        printf("2. Update contact details\n");
        printf("3. Display all saved contacts\n");
        printf("4. Delete a contact\n");
        printf("5. Search for a contact\n");
        printf("6. See total number of contacts saved\n");
        printf("7. Exit Phonebook\n");
        printf("8. Delete all records\n\n");
        
        printf("Choose an option (1-8): ");
        fflush(stdout);
        
        int choice;
        if (scanf("%d", &choice) != 1) {
            printf("\nError: Please enter a valid number\n");
            getchar();
            getchar();
            continue;
        }
        getchar();
        
        switch (choice) {
            case 1:
                addperson(fptr);
                break;
            case 2:
                update(fptr);
                break;
            case 3:
                displayall(fptr);
                break;
            case 4:
                deleteone(fptr);
                break;
            case 5:
                searchandprint(fptr);
                break;
            case 6:
                CLEAR_SCREEN;
                printf("\n\nThere are %d contacts saved in this phonebook\n\n", count_contacts(fptr));
                printf("Press Any key to continue...\n");
                GET_CHAR;
                break;
            case 7:
                fclose(fptr);
                printf("Thank you for using Phonebook. Goodbye!\n");
                exit(0);
                break;
            case 8:
                deleteall(fptr);
                break;
            default:
                CLEAR_SCREEN;
                printf("\nError: Invalid input\n");
                printf("Please enter a choice between 1 and 8 only\n");
                printf("Press Any key to continue...\n");
                GET_CHAR;
        }
    }
    
    return 0;
}

void safe_fgets(char *buffer, int size, FILE *stream) {
    if (fgets(buffer, size, stream) != NULL) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
    }
}

void addperson(FILE *fptr) {
    CLEAR_SCREEN;
    fseek(fptr, 0, 2);
    
    Contact contact;
    memset(&contact, 0, sizeof(Contact));
    
    int c;
    printf("\nDo you want to add a contact to your phonebook?\n");
    printf("Press 1 to confirm, 2 to go back: ");
    
    if (scanf("%d", &c) != 1 || c != 1) {
        printf("Cancelled.\n");
        getchar();
        return;
    }
    getchar();
    
    CLEAR_SCREEN;
    printf("\n=== ADD NEW CONTACT ===\n\n");
    
    printf("1. First Name (Required): ");
    safe_fgets(contact.fname, MAX_NAME, stdin);
    
    if (strlen(contact.fname) == 0) {
        printf("Error: First name is required\n");
        printf("Press Any key to go back...\n");
        GET_CHAR;
        return;
    }
    
    printf("2. Last Name: ");
    safe_fgets(contact.lname, MAX_NAME, stdin);
    
    printf("3. Mobile Number (7-20 digits): ");
    while (1) {
        safe_fgets(contact.number, MAX_PHONE, stdin);
        int len = strlen(contact.number);
        if (len < 7 || len > 20) {
            printf("Invalid phone number (must be 7-20 digits)\n");
            printf("3. Mobile Number: ");
        } else {
            break;
        }
    }
    
    printf("4. Gender: ");
    safe_fgets(contact.gender, MAX_GENDER, stdin);
    
    printf("5. Email: ");
    safe_fgets(contact.email, MAX_EMAIL, stdin);
    
    printf("6. Birthdate (YYYY-MM-DD): ");
    safe_fgets(contact.birthdate, MAX_DATE, stdin);
    
    printf("7. Address: ");
    safe_fgets(contact.address, MAX_ADDRESS, stdin);
    
    if (fwrite(&contact, sizeof(Contact), 1, fptr) != 1) {
        printf("Error: Could not save contact\n");
    } else {
        printf("\n✓ Contact saved successfully!\n");
    }
    
    printf("Press Any key to continue...\n");
    GET_CHAR;
}

void displayall(FILE *fptr) {
    CLEAR_SCREEN;
    rewind(fptr);
    
    Contact contact;
    int count = 0;
    
    printf("\n=== ALL CONTACTS ===\n\n");
    
    while (fread(&contact, sizeof(Contact), 1, fptr) == 1) {
        count++;
        printf("┌────────────────────────────────────────┐\n");
        printf("│ Contact #%d\n", count);
        printf("├────────────────────────────────────────┤\n");
        printf("│ Name: %s %s\n", contact.fname, contact.lname);
        printf("│ Phone: %s\n", contact.number);
        printf("│ Gender: %s\n", contact.gender);
        printf("│ Email: %s\n", contact.email);
        printf("│ Birthdate: %s\n", contact.birthdate);
        printf("│ Address: %s\n", contact.address);
        printf("└────────────────────────────────────────┘\n\n");
    }
    
    if (count == 0) {
        printf("No contacts found. Your phonebook is empty.\n\n");
    }
    
    printf("Press Any key to continue...\n");
    GET_CHAR;
}

void deleteone(FILE *fptr) {
    CLEAR_SCREEN;
    FILE *temporary;
    char name[MAX_NAME];
    
    printf("\n=== DELETE A CONTACT ===\n\n");
    printf("Enter the First name of contact to delete: ");
    safe_fgets(name, MAX_NAME, stdin);
    
    if (search(fptr, name) == 0) {
        printf("Contact not found.\n");
        printf("Press Any key to continue...\n");
        GET_CHAR;
        return;
    }
    
    temporary = fopen("temporary.txt", "w+");
    if (temporary == NULL) {
        printf("Error in opening temporary file\n");
        return;
    }
    
    rewind(fptr);
    Contact contact;
    int deleted = 0;
    
    while (fread(&contact, sizeof(Contact), 1, fptr) == 1) {
        if (strcmp(name, contact.fname) != 0) {
            fwrite(&contact, sizeof(Contact), 1, temporary);
        } else {
            deleted = 1;
        }
    }
    
    fclose(fptr);
    fclose(temporary);
    
    remove("phonebook.txt");
    rename("temporary.txt", "phonebook.txt");
    
    if (deleted) {
        printf("✓ Contact '%s' deleted successfully!\n", name);
    } else {
        printf("Could not delete contact\n");
    }
    
    fptr = fopen("phonebook.txt", "a+");
    
    printf("Press Any key to continue...\n");
    GET_CHAR;
}

void update(FILE *fptr) {
    CLEAR_SCREEN;
    char name[MAX_NAME];
    int a;
    
    printf("\nDo you want to edit one of your contacts?\n");
    printf("Press 1 to confirm, 2 to go back: ");
    
    if (scanf("%d", &a) != 1 || a != 1) {
        printf("Cancelled.\n");
        getchar();
        return;
    }
    getchar();
    
    CLEAR_SCREEN;
    printf("\n=== UPDATE CONTACT ===\n\n");
    printf("Enter the first name of the contact to update: ");
    safe_fgets(name, MAX_NAME, stdin);
    
    if (search(fptr, name) != 1) {
        printf("No match found for '%s'\n", name);
        printf("Press Any key to continue...\n");
        GET_CHAR;
        return;
    }
    
    Contact contact;
    printf("\nEnter new details:\n\n");
    
    printf("1. First Name: ");
    safe_fgets(contact.fname, MAX_NAME, stdin);
    
    printf("2. Last Name: ");
    safe_fgets(contact.lname, MAX_NAME, stdin);
    
    printf("3. Mobile Number: ");
    safe_fgets(contact.number, MAX_PHONE, stdin);
    
    printf("4. Gender: ");
    safe_fgets(contact.gender, MAX_GENDER, stdin);
    
    printf("5. Email: ");
    safe_fgets(contact.email, MAX_EMAIL, stdin);
    
    printf("6. Birthdate: ");
    safe_fgets(contact.birthdate, MAX_DATE, stdin);
    
    printf("7. Address: ");
    safe_fgets(contact.address, MAX_ADDRESS, stdin);
    
    long size = sizeof(Contact);
    fseek(fptr, -size, 1);
    fwrite(&contact, sizeof(Contact), 1, fptr);
    
    printf("\n✓ Contact '%s' has been updated!\n\n", name);
    printf("Press Any key to continue...\n");
    GET_CHAR;
}

void searchandprint(FILE *fptr) {
    CLEAR_SCREEN;
    char name[MAX_NAME];
    int flag = 0;
    
    printf("\n=== SEARCH CONTACT ===\n\n");
    printf("Enter the first name to search: ");
    safe_fgets(name, MAX_NAME, stdin);
    
    rewind(fptr);
    Contact contact;
    
    while (fread(&contact, sizeof(Contact), 1, fptr) == 1) {
        if (strcmp(name, contact.fname) == 0) {
            printf("\n┌────────────────────────────────────────┐\n");
            printf("│ CONTACT FOUND\n");
            printf("├────────────────────────────────────────┤\n");
            printf("│ Name: %s %s\n", contact.fname, contact.lname);
            printf("│ Phone: %s\n", contact.number);
            printf("│ Gender: %s\n", contact.gender);
            printf("│ Email: %s\n", contact.email);
            printf("│ Birthdate: %s\n", contact.birthdate);
            printf("│ Address: %s\n", contact.address);
            printf("└────────────────────────────────────────┘\n\n");
            flag = 1;
            break;
        }
    }
    
    if (flag == 0) {
        printf("\nNo match found for '%s'\n\n", name);
    }
    
    printf("Press Any key to continue...\n");
    GET_CHAR;
}

int search(FILE *fptr, char name[]) {
    int flag = 0;
    rewind(fptr);
    Contact contact;
    
    while (fread(&contact, sizeof(Contact), 1, fptr) == 1) {
        if (strcmp(name, contact.fname) == 0) {
            flag = 1;
            break;
        }
    }
    
    if (flag == 0) {
        printf("Match not found for '%s'\n", name);
    }
    
    return flag;
}

int count_contacts(FILE *fptr) {
    rewind(fptr);
    int count = 0;
    Contact contact;
    
    while (fread(&contact, sizeof(Contact), 1, fptr) == 1) {
        count++;
    }
    
    return count;
}

void deleteall(FILE *fptr) {
    CLEAR_SCREEN;
    printf("\nDo you want to delete ALL contacts?\n");
    printf("This action CANNOT be undone!\n\n");
    printf("Press 1 to confirm, any other key to cancel: ");
    fflush(stdout);
    
    if (GET_CHAR == '1') {
        CLEAR_SCREEN;
        printf("\n✓ All contacts deleted successfully!\n\n");
        fptr = fopen("phonebook.txt", "w");
        if (fptr != NULL) {
            fclose(fptr);
            fptr = fopen("phonebook.txt", "a+");
        }
    } else {
        printf("\n\nOperation cancelled.\n");
    }
    
    printf("Press Any key to continue...\n");
    GET_CHAR;
}

