#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include IMPL

#define max(a,b) ((a) > (b) ? (a) : (b))

#define update(e) \
    do { e->height = 1 + max(e->pLeft?e->pLeft->height:0, e->pRight?e->pRight->height:0); } while(0)

int rotateLeftCount = 0, rotateRightCount = 0;

entry *mallocEntry()
{
    entry *e = (entry *) malloc(sizeof(entry));
    e->pLeft = e->pRight = NULL;
    e->height = 0;
    return e;
}

entry *rotateLeft(entry* e)
{
    entry* temp = e->pRight;
    e->pRight = temp->pLeft;
    temp->pLeft = e;

    update(e);
    update(temp);
    return temp;
}

entry *rotateRight(entry* e)
{
    entry* temp = e->pLeft;
    e->pLeft = temp->pRight;
    temp->pRight = e;

    update(e);
    update(temp);
    return temp;
}

entry *balance(entry *e)
{
    update(e);
    entry *left = e->pLeft;
    entry *right = e->pRight;
    if (right->height > 1 + left->height) {
        if (right->pRight->height < right->pLeft->height) e->pRight = rotateRight(right);
        e = rotateLeft(e); // a
    } else if (left->height > 1 + right->height) {
        if (left->pLeft->height < left->pRight->height) e->pLeft = rotateLeft(left);
        e = rotateRight(e);
    }
    return e;
}

entry *_findName(char lastname[], entry *pHead)
{
    if (pHead->height == 0)
        return NULL;

    int cmp = strcmp(lastname, pHead->lastName);
    if (cmp == 0)
        return pHead;
    else if (cmp < 0)
        return _findName(lastname, pHead->pLeft);
    else // cmp > 0
        return _findName(lastname, pHead->pRight);
}

entry *_append(char lastName[], entry *e)
{
    if (e->height == 0) {
        strcpy(e->lastName, lastName);
        e->height = 1;
        e->pLeft = mallocEntry();
        e->pRight = mallocEntry();
        return e;
    }

    int cmp = strcmp(lastName, e->lastName);
    if (cmp < 0)
        e->pLeft = _append(lastName, e->pLeft);
    else if (cmp > 0)
        e->pRight = _append(lastName, e->pRight);
    else
        return e;

    return balance(e);
}

phonebook *create()
{
    phonebook *book = (phonebook *) malloc(sizeof(phonebook));
    book->pHead = mallocEntry();
    return book;
}

entry *findName(char lastname[], phonebook *book)
{
    return _findName(lastname, book->pHead);
}

entry *append(char lastName[], phonebook *book)
{
    entry *e = _append(lastName, book->pHead);
    book->pHead = e;
    return e;
}

void _release(entry *e)
{
    if (e != NULL)
    {
        _release(e->pLeft);
        _release(e->pRight);
        e->pLeft = e->pRight = NULL;
        free(e);
    }
}

void release(phonebook *book) 
{
    _release(book->pHead);
    book->pHead = NULL;
    free(book);
}

#undef max
#undef update
