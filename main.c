#include "arg_handler.h"
#include "cli.h"


int
main(int argc, char ** argv)
{
    // Check if proper amount of arguments went into main
    if (argc != 2)
    {
        printf("USAGE: %s <input filename>\n", argv[0]);
        return 1;
    }

    char * string = get_file(argv[1]);

    if (strcmp(string, ERROR_CODE) == 0)
    {
        return 1;
    }

    remove_comments(string);

    int x = 0, y = 0, p = 0, width, height, depth;
    char * type;
    int * w = &width;
    int * h = &height;
    int * d = &depth;

    get_dimensions(type, w, h, d, string);

    string = strtok (NULL, " \n");

    int red[width][height];
    int green[width][height];
    int blue[width][height];


    while (string != NULL) // Generate tokens as long as you dont encounter NULL
    {
        printf("p = %d\t, p%3 = %d\t, string = %s\t, x = %d\t, y = %d\n",p,p%3, string ,x,y);
        switch(p % 3)
        {
          case 0: red[x][y] = atoi(string);break;
          case 1: green[x][y] = atoi(string); break;
          case 2: blue[x][y] = atoi(string);x++;break;
        }
        if ( x == width)
        {
            x = 0;
            y++;
        }
        p++;
        string = strtok (NULL, " \n");
    }

    run_cli(width, height);

    return 0;
}
