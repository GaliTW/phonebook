#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include IMPL

/* list version */
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
    return book;
}

entry *findName(char lastname[], phonebook *book)
{
    if (book == NULL)
        return NULL;

    entry* e = book->pHead;
    while (e->pNext != NULL) {
        if (strcmp(lastname, e->lastName) == 0)
            return e;
        e = e->pNext;
    }
    return NULL;
}

entry *append(char lastName[], phonebook *book)
{
    /* allocate memory for the new entry and put lastName */
    entry *e = mallocEntry();
    strcpy(book->pEnd->lastName, lastName);
    book->pEnd = book->pEnd->pNext = e;

    return e;
}

void release(phonebook *book) 
{
    for (entry* walk = book->pHead, *tmp; walk != NULL; )
    {
        tmp = walk;
        walk = walk->pNext;
        free(tmp);
    }
    book->pHead = book->pEnd = NULL;
    free(book);
}
