#include <string>
#include <iostream>
#include <cstdio>
#include <cerrno>

std::string get_file_contents(const char *filename)
{
    std::FILE *filepath = std::fopen(filename, "rb");
    if (filepath)
    {
            std::string contents;
            std::fseek(filepath, 0, SEEK_END);
            contents.resize(std::ftell(filepath));
            std::rewind(filepath);
            std::fread(&contents[0], 1, contents.size(), filepath);
            std::fclose(filepath);
            return(contents);
    }
    throw(errno);
}

int main()
{
    std::string file = get_file_contents("ex1short.ppm");
    std::cout<<file<<std::endl;
    std::cout<<file[3]<<std::endl;
}
