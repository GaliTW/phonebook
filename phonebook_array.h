#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H

#define MAX_LAST_NAME_SIZE 16
#define ARRAY_SIZE 500

/* array version */
typedef struct __PHONE_BOOK_ENTRY {
    char firstName[16];
    char email[16];
    char phone[10];
    char cell[10];
    char addr1[16];
    char addr2[16];
    char city[16];
    char state[2];
    char zip[5];
} detail_entry;

typedef struct __LAST_NAME_ENTRY {
    char collectLastName[ARRAY_SIZE][MAX_LAST_NAME_SIZE];
    detail_entry *collectDetail[ARRAY_SIZE];
    char *lastName;
    char *detail;
    struct __LAST_NAME_ENTRY *pNext;
} entry;

typedef struct __PHONE_BOOK {
    entry *pHead;
    entry *pEnd;
    int currentSize;
} phonebook;

phonebook *create();
entry *findName(char lastname[], phonebook *book);
entry *append(char lastName[], phonebook *book);
void release(phonebook *book);

#endif
