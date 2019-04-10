#include "image.h"
#include "colors.h"

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <fstream>

Image::Image (char* string)
{
    type = strtok (string, " \n");
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

int
Image::get_width() {return width;}

int
Image::get_height() {return height;}

int
Image::get_color_depth() {return color_depth;}

int
Image::get_type() { return type[1]; }// 50 - pgm, 51 - ppm

void
Image::write()
{
    if( type[1] == 51)
    {
    std::ofstream output_file("./output.ppm");
    output_file << type <<"\n" << width << " " << height << "\n" <<color_depth << "\n";
        for(size_t j = 0; j < height; j++)
        {
            for(size_t i = 0; i < width; i++)
            {
                output_file << red[j][i] << "\n" << green[j][i] << "\n" <<  blue[j][i] <<"\n";
            }
        }
    } else if (type[1] == 50)
    {
    std::ofstream output_file("./output.pgm");
    output_file << type <<"\n" << width << " " << height << "\n" <<color_depth << "\n";
        for(size_t j = 0; j < height; j++)
        {
            for(size_t i = 0; i < width; i++)
            {
                output_file << red[j][i] << "\n";
            }
        }

    }
}

void
Image::fill(char * string)
{

    string = strtok (NULL, " \n");// eliminate the first token (useless)

    int x = 0, color = 0, y=0;

    while (string != NULL) // generate tokens as long as you don't encounter NULL
    {
        if(get_type() == 51)
        {
            switch(color % 3)
            {
              case 0: t_red[x] = atoi(string);break;
              case 1: t_green[x] = atoi(string); break;
              case 2: t_blue[x] = atoi(string);x++;break;
            }
            if ( x == width)
            {
                red[y] = t_red;
                green[y] = t_green;
                blue[y] = t_blue;
                x = 0;
                y++;
            }

            color++;
        } else if(get_type() == 50)
        {
            t_red[x] = atoi(string);
            //printf("%d\t",t_red[x]);
            x++;
            if (x == width)
            {
                red[y] = t_red;
                x = 0;
                y++;
                //printf("\n");
            }
        }
        string = strtok (NULL, " \n");

    }
}

void
Image::print()
{
    if(get_type() == 51)//ppm
    {
        for (size_t i = 0; i < height; i++)
        {
            for (size_t j = 0; j < width; j++)
            {
                printf("%s%d %s%d %s%d%s \t",RED,red[i][j],GRN, green[i][j], BLU, blue[i][j], NRM);
            }
            printf("\n");
        }
    } else if (get_type() == 50)//pgm
    {
        for (size_t i = 0; i < height; i++)
        {
            for (size_t j = 0; j < width; j++)
            {
                printf("%s%d \t",CYN, red[i][j]);
            }
            printf("\n%s",NRM);
        }
    }
}

void
Image::crop(int x1, int y1, int x2, int y2)
{
    height = y2-y1+1;
    width = x2-x1+1;

    for(size_t i = 0; i < height; i++)
    {
        red[i] = red[i+y1 - 1];
        green[i] = green[i+y1 - 1];
        blue[i] = blue[i+y1 - 1];

        for(size_t k = 0; k < width; k++)
        {
            red[i][k] = red[i][k+x1-1];
            green[i][k] = green[i][k+x1-1];
            blue[i][k] = blue[i][k+x1-1];
        }
        red[i].resize(width);
        green[i].resize(width);
        blue[i].resize(width);
    }

    red.resize(height);
    green.resize(height);
    blue.resize(height);
}

void
Image::flip(char orientation)
{
    if(orientation == 'v')
    {
        for(size_t i = 0; i < height; i++)
        {
            std::reverse(red[i].begin(), red[i].end());
            std::reverse(green[i].begin(), green[i].end());
            std::reverse(blue[i].begin(), blue[i].end());
        }
    } else if (orientation == 'h')
    {
        std::reverse(red.begin(), red.end());
        std::reverse(green.begin(), green.end());
        std::reverse(blue.begin(), blue.end());

    }
    print();
}

void
Image::zoom()
{
    int n=1;
    std::vector<short int> row;
    std::vector<std::vector<short int> > r_col;
    std::vector<std::vector<short int> > g_col;
    std::vector<std::vector<short int> > b_col;
    row.resize(width,0);
    r_col.resize(height,row);
    g_col.resize(height,row);
    b_col.resize(height,row);

    while(1)
    {
        printf("podaj n: ");
        scanf("%u",&n);
        if(n <= 0 || n >= width || n >= height){
            continue;
        }
            printf("zoomed %d times the image\n",n);
    }
}

void
Image::rmcolor()
{
    char color;
    std::vector<short int> z(width,0);

    while(color = getchar())
    {
        printf("który kolor? [c]zerwony/[z]ielony/[n]iebieski\n");
        color = getchar();
        if(color == 'c')
        {
            std::fill(red.begin(),red.end(),z);
            break;
        } else if (color == 'z')
        {
            std::fill(green.begin(),green.end(),z);
            break;
        } else if(color == 'n')
        {
            std::fill(blue.begin(),blue.end(),z);
            break;
        } else break;
    }
}

void
Image::puzzle()
{
    int n, x,y;

    while(1)
    {
        printf("podaj n: ");
        scanf("%d", &n);

        if (n > width || n > height)
        {
            printf("n jest za duże jak na to zdjęcie\n");
            continue;
        }
        break;
    }

    int nowe_width = width - width % n;
    int nowe_height = height - height % n;
    // ilość "kostek" w x i y
    x = nowe_width/n;
    y = nowe_height/n;

    crop(1,1,nowe_width,nowe_height);

    std::vector<short int> row;
    std::vector<std::vector<short int> > col;
    std::vector<std::vector<std::vector<short int> > > r_base;
    std::vector<std::vector<std::vector<short int> > > g_base;
    std::vector<std::vector<std::vector<short int> > > b_base;

    row.resize(n,0);
    col.resize(n,row);
    r_base.resize(x*y,col);
    g_base.resize(x*y,col);
    b_base.resize(x*y,col);

    int k = 0;
    for(size_t j = x; j>= 1; j--)
    {
        for(size_t i = y; i >= 1; i--)
        {
                for(short int p = 0; p <= n-1; p++)
                {
                    for(short int q = 0; q <= n-1; q++)
                    {
                        r_base[k][p][q] = red[(y-i)*n + p][(x-j)*n + q];
                        g_base[k][p][q] = green[(y-i)*n + p][(x-j)*n + q];
                        b_base[k][p][q] = blue[(y-i)*n + p][(x-j)*n + q];
                    }
                }
        k++;
        }
    }

    // Fisher-Yates
    srand(time(NULL));
    for (size_t i = 0; i < x*y; i++)
    {
        int j = i + rand() % (x*y - i);
        swap(r_base[i],r_base[j]);
        swap(g_base[i],g_base[j]);
        swap(b_base[i],b_base[j]);
    }

    k=0;
    for(size_t j = x; j>= 1; j--)
    {
        for(size_t i = y; i >= 1; i--)
        {
                for(short int p = 0; p <= n-1; p++)
                {
                    for(short int q = 0; q <= n-1; q++)
                    {
                        red[(y-i)*n + p][(x-j)*n + q] = r_base[k][p][q];
                        green[(y-i)*n + p][(x-j)*n + q] = g_base[k][p][q];
                        blue[(y-i)*n + p][(x-j)*n + q] = b_base[k][p][q];
                    }
                }
        k++;
        }
    }
}
