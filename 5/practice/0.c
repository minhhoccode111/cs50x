#include <stdio.h>
#include <stdlib.h>

// implement linked lists add new node by prepend
typedef struct node
{
    int value;
    struct node* next;
} node;

void freeList(node *list)
{
    if (list == NULL) return;
    freeList(list->next);
    free(list);
}

int main(int argc, char* argv[])
{
    // define a pointer which will be pointed to a node (to hold the head)
    node *list = NULL;

    // loop through each CLI argument
    for (int i = 1; i < argc; i++)
    {
        // current CLI number as string 
        char *current = argv[i];

        // convert to number
        int number = atoi(current);

        // allocate memory for current node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            // free the list
            freeList(list);
            return 1;
        }


        // assign value to current node
        (*n).value = number; 

        // prepending current node at the start of the list
        // by making current node.next to hold the existing list
        (*n).next = list;

        // make the list pointer to point to current node
        // because the current node already hold the hold list with it.next
        list = n;
    }

    // travail through the list
    // define a pointer which point to the same head that list pointer is pointing to
    for (node* ptr = list; ptr != NULL; ptr = (*ptr).next)
    {
        // while ptr is pointing to a node (not NULL)
        // print the current node (which ptr is pointing to)
        printf("%i\n", (*ptr).value);
        // make ptr point to the next node in the list
    }

    freeList(list);

    return 0;
}
