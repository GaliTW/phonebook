#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

#include IMPL

/* array version */
entry *mallocEntry()
{
    entry *e = (entry *) malloc(sizeof(entry));
    e->pNext = NULL;
    return e;
}

phonebook *create()
{
    phonebook *book = (phonebook *) malloc(sizeof(phonebook));
    book->pHead = book->pEnd = mallocEntry();
    book->currentSize = 0;
    return book;
}

entry *findName(char lastname[], phonebook *book)
{
    if (book == NULL)
        return NULL;

    int size;
    entry* e = book->pHead;
    while (e != NULL) {
        if (e->pNext == NULL)
            size = book->currentSize;
        else
            size = ARRAY_SIZE;

        for ( int i = 0 ; i < size ; ++i ) {
            if (strcmp(lastname, e->collectLastName[i]) == 0) {
                e->lastName = e->collectLastName[i];
                // pHead->detail = e->collectDetail[i];
                return e;
            }
        }
        e = e->pNext;
    }
    return NULL;
}

entry *append(char lastName[], phonebook *book)
{
    /* allocate memory for the new entry and put lastName */
    entry *e = book->pEnd;
    strcpy(e->collectLastName[book->currentSize++], lastName);
    if (book->currentSize == ARRAY_SIZE) {
        book->pEnd = e->pNext = mallocEntry();
        book->currentSize = 0;
    }

    return e;
}
