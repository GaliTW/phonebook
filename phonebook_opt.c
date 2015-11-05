#include <stdlib.h>

#include "phonebook_opt.h"

/* FILL YOUR OWN IMPLEMENTATION HERE! */
entry *mallocEntry()
{
    entry *e = (entry *) malloc(sizeof(entry));
    e->pNext = NULL;
    return e;
}

phonebook *create()
{
    phonebook *book = (phonebook *) malloc(sizeof(phonebook));
    book->pHead = mallocEntry();
    return book;
}

entry *findName(char lastname[], phonebook *book)
{
    /* TODO: implement */
    return NULL;
}

entry *append(char lastName[], phonebook *book)
{
    return NULL;
}

void release(phonebook *book) 
{
    
}
