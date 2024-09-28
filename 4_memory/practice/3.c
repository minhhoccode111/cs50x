#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    // open csv file
    FILE *file = fopen("phonebook.csv","a");

    if (file == NULL)
    {
        return 1;
    }

    // get name and number 
    char *name = get_string("Name: ");
    char *number = get_string("Number: ");

    // print to file
    fprintf(file, "%s, %s\n", name, number);

    // close file
    fclose(file);
}
