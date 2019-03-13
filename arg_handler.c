#include "arg_handler.h"

void remove_element(char *array, int index, int amount, int array_length)
{
    int i;
    for (i = index; i < array_length - 1; i++) array[i] = array[i+amount];
}

void remove_comments(char *string)
{
    bool comment = false;
    int whitespace = 0;

    for (size_t i = 0; i < strlen(string); i++) // iterate over whole string
    {
        if (string[i] == '#') // '#' char starts comments
        {
            for (size_t j=i; ; j++) // increase i until end of comment
            {
                if(string[j] == '\n' && string[j + 1] != '#') // In case of multiline comments!
                {
                    remove_element(string , i, j+1 - i, strlen(string));
                    break;
                }
            }
        }
    }
}
