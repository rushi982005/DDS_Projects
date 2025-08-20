#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Contact {
    char name[50];
    char phone[15];
    struct Contact* next;
} Contact;

Contact* head = NULL;

Contact* createContact(char* name, char* phone) {
    Contact* newC = (Contact*)malloc(sizeof(Contact));
    strcpy(newC->name, name);
    strcpy(newC->phone, phone);
    newC->next = NULL;
    return newC;
}

void addContact(char* name, char* phone) {
    Contact* newC = createContact(name, phone);
    if(head == NULL || strcmp(name, head->name) < 0) {
        newC->next = head;
        head = newC;
        return;
    }
    Contact* temp = head;
    while(temp->next && strcmp(name, temp->next->name) > 0)
        temp = temp->next;
    newC->next = temp->next;
    temp->next = newC;
}

void displayContacts() {
    Contact* temp = head;
    while(temp) {
        printf("%s - %s\n", temp->name, temp->phone);
        temp = temp->next;
    }
}

Contact* searchContact(char* name) {
    Contact* temp = head;
    while(temp) {
        if(strcmp(temp->name, name) == 0) return temp;
        temp = temp->next;
    }
    return NULL;
}

void deleteContact(char* name) {
    Contact* temp = head, *prev = NULL;
    while(temp && strcmp(temp->name, name) != 0) {
        prev = temp;
        temp = temp->next;
    }
    if(temp == NULL) return;
    if(prev == NULL) head = temp->next;
    else prev->next = temp->next;
    free(temp);
}

int main() {
    int ch; char name[50], phone[15];
    do {
        printf("\n1.Add 2.Display 3.Search 4.Delete 5.Exit\nChoice: ");
        scanf("%d", &ch);
        switch(ch) {
            case 1: printf("Name: "); scanf("%s", name);
                    printf("Phone: "); scanf("%s", phone);
                    addContact(name, phone); break;
            case 2: displayContacts(); break;
            case 3: printf("Name to search: "); scanf("%s", name);
                    Contact* c = searchContact(name);
                    if(c) printf("Found: %s - %s\n", c->name, c->phone);
                    else printf("Not found!\n"); break;
            case 4: printf("Name to delete: "); scanf("%s", name);
                    deleteContact(name); break;
        }
    } while(ch != 5);
    return 0;
}
