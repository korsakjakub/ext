#include "arg_handler.h"
#include "cli.h"
#include "image.h"
#include <string>
#include <experimental/filesystem>
#include <iostream>

//namespace fs = std::experimental::filesystem;

/*
void does_file_exist(const fs::path& p, fs::file_status s = fs::file_status{})
{
    if(fs::status_known(s) ? fs::exists(s) : fs::exists(p))
        std::cout<<"exists\n";
    else
        std::cout<<"nexists\n";
}
*/

int main(int argc, char ** argv)
{
    // Check if proper amount of arguments went into main
    if (argc != 2)
    {
        printf("USAGE: %s <input filename>\n", argv[0]);
        return 1;
    }
    //std::string input(argv[1]);

    char * string = get_file(argv[1]);

    if (atoi(string) == -1)
    {
        return 1;
    }

    remove_comments(string);

    Image image(string);
    image.fill(string);
    run_cli(image);

    return 0;
}
