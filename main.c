#include "arg_handler.h"

void get_color_components(char * string, int * red, int * green, int * blue)
{

}

int
main(int argc, char ** argv)
{

    struct stat st;
    int file;
    char * string;

    // Check if proper amount of arguments went into main
    if (argc != 2)
    {
        printf("USAGE: %s <input filename>\n", argv[0]);
        return 1;
    }

    // Try to open the file
    file = open(argv[1], O_RDONLY);
    if (file < 0)
    {
        perror("Error opening file");
        return 1;
    }


    // Get its size in bytes
    if (fstat(file, &st) < 0) {   // Check if succesful
        perror("Error getting file size");
        return 1;
    }

    // Get that much memory for the string
    // But get 1 byte more, to store the '\0' to terminate the string.
    string = malloc(st.st_size + 1);   // 1 byte more
    if (string == NULL) // Check we really got it.
    {
        fprintf(stderr, "Error: out of memory.\n");
        return 1;
    }

    // Read the entire file into string.
    if (read(file, string, st.st_size) < 0)
    {
        perror("Error reading the file");
        return 1;
    }

    // Make sure the string is terminated.
    string[st.st_size] = '\0';

    remove_comments(string);

    int width = 0, height = 0, depth = 0, x = 0, y = 0, p = 0;
    char* type;
    char * pch;

    pch = strtok (string, " \n");
    type = pch;
    pch = strtok (NULL, " \n");
    width = atoi(pch);
    pch = strtok (NULL, " \n");
    height = atoi(pch);
    pch = strtok (NULL, " \n");
    depth = atoi(pch);
    pch = strtok (NULL, " \n");

    int red[width][height];
    int green[width][height];
    int blue[width][height];

    while (pch != NULL) // Generate tokens as long as you dont encounter NULL
    {
        printf("p = %d\t, p%3 = %d\t, pch = %s\t, x = %d\t, y = %d\n",p,p%3, pch,x,y);
        switch(p % 3)
        {
          case 0: red[x][y] = atoi(pch);break;
          case 1: green[x][y] = atoi(pch); break;
          case 2: blue[x][y] = atoi(pch);x++;break;
        }
        if ( x == width)
        {
            x = 0;
            y++;
        }
        p++;
        pch = strtok (NULL, " \n");
    }

    return 0;
}
