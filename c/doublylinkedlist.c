#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// clear && gcc doublylinkedlist.c -o doublylinkedlist && ./doublylinkedlist && rm ./doublylinkedlist

typedef struct node {
    int item;
    struct node *prev, *next;
} node;

node *head, *tail;

void insert(int item, bool at_tail)
{
    node *ptr = (node*) malloc(sizeof(node));
    ptr->item = item;
    ptr->prev = ptr->next = NULL;

    if (NULL == head) {
        head = tail = ptr;
    } else if (at_tail) {
        tail->next = ptr;
        ptr->prev = tail;
        tail = ptr;
    } else {
        ptr->next = head;
        head->prev = ptr;
        head = ptr;
    }
}

int delete(bool from_tail)
{
    if (NULL == head) {
        printf("Empty list.\n");
        exit(1);
    } else if (from_tail) {
        node *ptr = tail;
        int item = ptr->item;
        tail = ptr->prev;
        if (NULL == tail) head = tail;
        else tail->next = NULL;
        free(ptr);
        ptr = NULL;
        return item;
    } else {
        node *ptr = head;
        int item = ptr->item;
        head = ptr->next;
        if (NULL == head) tail = head;
        else head->prev = NULL;
        free(ptr);
        ptr = NULL;
        return item;
    }
}

void list()
{
    node *ptr = head;

    while (NULL != ptr) {
        printf("%d ", ptr->item);
        ptr = ptr->next;
    }

    printf("\n");
}

int main(int argc, char *argv[])
{
    for (int i = 1; i <= 10; i++)
        insert(i, i < 6);

    list(); // 10 9 8 7 6 1 2 3 4 5

    for (int i = 1; i <= 4; i++)
        delete(i < 3);

    list(); // 8 7 6 1 2 3
}