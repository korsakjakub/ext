#include "arg_handler.h"

void
remove_element(char *array, int index, int amount, int array_length)
{
    int i;
    for (i = index; i < array_length - 1; i++) array[i] = array[i+amount];
}

void
remove_comments(char *string)
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


char *
get_file(char * path)
{
    char * string;
    struct stat st;
    int file;


    // Try to open the file
    file = open(path, O_RDONLY);
    if (file < 0)
    {
        perror("Error opening file");
        return ERROR_CODE;
    }


    // Get its size in bytes
    if (fstat(file, &st) < 0) {   // Check if succesful
        perror("Error getting file size");
        return ERROR_CODE;
    }

    // Get that much memory for the string
    // But get 1 byte more, to store the '\0' to terminate the string.
    string = malloc(st.st_size + 1);   // 1 byte more
    if (string == NULL) // Check we really got it.
    {
        fprintf(stderr, "Error: out of memory.\n");
        return ERROR_CODE;
    }

    // Read the entire file into string.
    if (read(file, string, st.st_size) < 0)
    {
        perror("Error reading the file");
        return ERROR_CODE;
    }

    // Make sure the string is terminated.
    string[st.st_size] = '\0';

    return string;
}

void
get_dimensions(char * type, int * width, int * height, int * depth, char * string)
{
    string = strtok (string, " \n");
    type = string;
    string = strtok (NULL, " \n");
    *width = atoi(string);
    string = strtok (NULL, " \n");
    *height = atoi(string);
    string = strtok (NULL, " \n");
    *depth = atoi(string);

}
