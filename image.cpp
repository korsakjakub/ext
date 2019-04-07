#include "image.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Image::Image (char* string)
{
    string = strtok (string, " \n");
    string = strtok (NULL, " \n");
    width = atoi(string);
    string = strtok (NULL, " \n");
    height = atoi(string);
    string = strtok (NULL, " \n");
    color_depth = atoi(string);

    t_red.resize(width,0);
    t_green.resize(width,0);
    t_blue.resize(width,0);
    red.resize(height,t_red);
    green.resize(height,t_green);
    blue.resize(height,t_blue);
}

int Image::get_width() {return width;}
int Image::get_height() {return height;}
int Image::get_color_depth() {return color_depth;}
void Image::fill(char * string)
{

    string = strtok (NULL, " \n");// eliminate the first token (useless)

    int x = 0, color = 0, y=0;

    while (string != NULL) // generate tokens as long as you don't encounter NULL
    {
        switch(color % 3)
        {
          case 0: t_red[x] = atoi(string);break;
          case 1: t_green[x] = atoi(string); break;
          case 2: t_blue[x] = atoi(string);x++;break;
        }
        if ( x == width)
        {
            x = 0;
            y++;
            red[y] = t_red;
            green[y] = t_green;
            blue[y] = t_blue;
        }

        color++;
        string = strtok (NULL, " \n");

    }
}
void Image::print()
{
    for (size_t i = 0; i < width; i++)
    {
        for (size_t j = 0; j < height; j++)
        {
            printf("%d\t %d\t %d\n",red[i][j], green[i][j], blue[i][j]);
        }
    }
}
