#include <stdio.h>
#include <stdlib.h>

// implement linked lists that sorted
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
    node *list = NULL;

    // through through every item in the CLI
    for (int i = 1; i < argc; i++)
    {
        char *string = argv[i];

        int number = atoi(string);

        node *currentNode = malloc(sizeof(node));
        if (currentNode == NULL)
        {
            freeList(list);
            return 1;
        }

        // assign value to the list
        currentNode->value = number; 
        currentNode->next = NULL; 

        // the list is empty
        if (list == NULL)
        {
            list = currentNode;
        }
        // current node belongs to the beginning of the list
        else if (currentNode->value < list->value)
        {
            // then prepend to beginning of the list
            currentNode->next = list;
            list = currentNode;
        }
        // current node belongs later in the list
        else 
        {
            // go through the list to insert
            for (node *ptr = list; ptr != NULL; ptr = ptr->next)
            {
                // if reach the end
                if (ptr->next == NULL)
                {
                    // append
                    ptr->next = currentNode;
                }
                // if less than the next node of the pointer
                else if (currentNode->value < ptr->next->value)
                {
                    // insert
                    currentNode->next = ptr->next;
                    ptr->next = currentNode;
                    break;
                }
                // else continue moving pointer
            }
        }
    }

    // will print the sorted list
    for (node* ptr = list; ptr != NULL; ptr = (*ptr).next)
    {
        printf("%i\n\n|\nv\n\n", ptr->value);
        if (ptr->next == NULL)
        {
            printf("NULL\n");
        }
    }

    freeList(list);

    return 0;
}

