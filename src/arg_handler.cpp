#include "arg_handler.h"

std::string remove_comments(std::string input)
{
    bool done = false;

    for (size_t i = 0; i < input.length(); i++) // iterate over whole string
    {
        if (input[i] == '#') // '#' char starts comments
        {
            for (size_t j=i; ; j++) // increase i until end of comment
            {
                if(input[j] == '\n' && input[j + 1] != '#') // In case of multiline comments start again
                {
                    input.erase(input.begin()+i, input.begin() + i + j - 2);
                    done = true;
                    break;
                }
            }
        }
        if(done)break;
    }
    return input;
}


std::string get_file(std::string path)
{
    std::string file;
    std::ifstream inFile;
    inFile.open(path);

    std::stringstream strStream;
    strStream << inFile.rdbuf();
    file = strStream.str();
    return file;
}
