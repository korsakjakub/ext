#include "arg_handler.h"
#include "cli.h"
#include "image.h"

int main(int argc, char ** argv)
{
    // Check if proper amount of arguments went into main
    if (argc != 2)
    {
        printf("USAGE: %s <input filename>\n", argv[0]);
        return 1;
    }

    char * string = get_file(argv[1]);

    if (atoi(string) == -1)
    {
        return 1;
    }

    remove_comments(string);

    Image image(string);
    image.fill(string);
    //image.print();
    run_cli(image);

    return 0;
}
