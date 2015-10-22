#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include IMPL

#define grandparent(e) ((e->pParent==NULL)?NULL:e->pParent->pParent)

#define uncle(e) ((grandparent(e)==NULL)?NULL:((e->pParent==grandparent(e)->pLeft)?grandparent(e)->pRight:grandparent(e)->pLeft))

int rotateLeftCount = 0, rotateRightCount = 0;
entry *mallocEntry(entry* parent)
{
    entry *e = (entry *) malloc(sizeof(entry));
    e->pLeft = e->pRight = NULL;
    e->pParent = parent;
    e->color = NONE;
    return e;
}

entry *rotateRight(entry *e)
{
    entry *father = e->pParent;
    entry *grandparent = grandparent(e);
    entry *temp = e->pRight;

    father->pLeft = temp;
    temp->pParent = father;

    e->pRight = father;
    father->pParent = e;

    e->pParent = grandparent;
    if (grandparent != NULL) {
        if (grandparent->pLeft == father)
            grandparent->pLeft = e;
        else
            grandparent->pRight = e;
    }

    return e;
}

entry *rotateLeft(entry* e)
{
    entry *father = e->pParent;
    entry *grandparent = grandparent(e);
    entry *temp = e->pLeft;

    father->pRight = temp;
    temp->pParent = father;

    e->pLeft = father;
    father->pParent = e;

    e->pParent = grandparent;
    if (grandparent != NULL) {
        if (grandparent->pRight == father)
            grandparent->pRight = e;
        else
            grandparent->pLeft = e;
    }

    return e;
}

entry *balance(entry *e)
{
    entry *father = e->pParent;
    entry *uncle = uncle(e);
    entry *grandparent = grandparent(e);

    if (father == NULL)
        e->color = BLACK;
    else if (father->color == RED) {
        if (uncle->color == RED) {
            father->color = uncle->color = BLACK;
            grandparent->color = RED;
            e = balance(grandparent);
        } else {
            if (e == father->pRight && father == grandparent->pLeft) {
                rotateLeft(e);
                rotateRight(e);
                e->color = BLACK;
                e->pLeft->color = e->pRight->color = RED;
            } else if (e == father->pLeft && father == grandparent->pRight) {
                rotateRight(e);
                rotateLeft(e);
                e->color = BLACK;
                e->pLeft->color = e->pRight->color = RED;
            } else if (e == father->pLeft && father == grandparent->pLeft) {
                father->color = BLACK;
                grandparent->color = RED;
                e = rotateRight(father);
            } else if (e == father->pRight && father == grandparent->pRight) {
                father->color = BLACK;
                grandparent->color = RED;
                e = rotateLeft(father);
            }
        }
    }
    return e;
}

entry *_findName(char lastname[], entry *pHead)
{
    if (pHead->color == NONE)
        return NULL;

    int cmp = strcmp(lastname, pHead->lastName);
    if (cmp == 0)
        return pHead;
    else if (cmp < 0)
        return _findName(lastname, pHead->pLeft);
    else // cmp > 0
        return _findName(lastname, pHead->pRight);
}

entry *_append(char lastName[], entry *e, entry *parent)
{
    if (e->color == NONE) {
        strcpy(e->lastName, lastName);
        e->pLeft = mallocEntry(e);
        e->pRight = mallocEntry(e);
        e->color = (parent == NULL)?BLACK:RED;
        return balance(e);
    } else {
        int cmp = strcmp(lastName, e->lastName);
        if (cmp < 0)
            e = _append(lastName, e->pLeft, e);
        else if (cmp > 0)
            e = _append(lastName, e->pRight, e);
    }

    return e;
}

phonebook *create()
{
    phonebook *book = (phonebook *) malloc(sizeof(phonebook));
    book->pHead = mallocEntry(NULL);
    return book;
}

entry *findName(char lastname[], phonebook *book)
{
    return _findName(lastname, book->pHead);
}

entry *append(char lastName[], phonebook *book)
{
    entry *e = _append(lastName, book->pHead, NULL);
    if (e->pParent == NULL)
        book->pHead = e;
    return e;
}

#undef grandparent
#undef uncle
