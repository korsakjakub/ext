#include "arg_handler.h"
#include "cli.h"
#include "image.h"
#include <string>
#include <filesystem>
#include <iostream>
#include <fstream>



bool does_file_exist(const std::string& name)
{
    std::ifstream f(name.c_str());
    return f.good();
}

int main(int argc, char ** argv)
{
    // Check if proper amount of arguments went into main
    if (argc != 2)
    {
        printf("USAGE: %s <input filename>\n", argv[0]);
        return 1;
    }

    std::string input(argv[1]);

    if(does_file_exist(input)){
        std::string file = get_file(input);
        for(auto &s : file){
            std::cout<<s;
        }
        file = remove_comments(file);
        std::cout<<std::endl;
        for(auto &s : file){
            std::cout<<s;
        }


        /*
        Image image(string);
        image.fill(string);
        run_cli(image);
        */
    }
    else {
        std::cout<<"Plik nie istnieje: "<<input<<"\n";
        return 1;
    }
    return 0;
}
