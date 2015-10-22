#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H

#define MAX_LAST_NAME_SIZE 16

/* list malloc detail version */
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
    char lastName[MAX_LAST_NAME_SIZE];
    detail_entry *detail;
    struct __LAST_NAME_ENTRY *pNext;
} entry;

typedef struct __PHONE_BOOK {
    entry *pHead;
    entry *pEnd;
} phonebook;

phonebook *create();
entry *findName(char lastname[], phonebook *book);
entry *append(char lastName[], phonebook *book);

#endif
