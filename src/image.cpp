#include "image.h"
#include "colors.h"

#include <time.h>
#include <iostream>
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
    std::string file_path;
    do{
        printf("Podaj nazwę pliku:\n");
        std::cin>>file_path;
    }while(file_path.empty());

    if( type[1] == 51)
    {
    std::ofstream output_file("output/" + file_path + ".ppm");
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
        std::ofstream output_file("output/" + file_path + ".pgm");
        output_file << type <<"\n" << width << " " << height << "\n" <<color_depth << "\n";
        for(size_t j = 0; j < height; j++)
        {
            for(size_t i = 0; i < width; i++)
            {
                output_file << red[j][i] << "\n";
            }
        }
    }
    printf("Zapisano pomyślnie.\n");
    pause();
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
            x++;
            if (x == width)
            {
                red[y] = t_red;
                x = 0;
                y++;
            }
        }
        string = strtok (NULL, " \n");

    }
}

void
Image::print()
{
    if(width < 200 && height < 200)
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
}
void
Image::fill_with_value(doubleVector &arr, short int value)
{
    for(size_t i = 0; i < arr.size(); i++)
    {
        for(size_t j = 0; j < arr.size(); j++)
        {
            arr[i][j] = value;
        }
    }
}

void
Image::zoom()
{
    int n=1, x, y;

    while(1)
    {
        printf("podaj n: ");
        scanf("%d",&n);
        if(n <= 0 || n >= width || n >= height || height/n <= n || width/n <= n){
            continue;
        }
        break;
    }

    x = round_to_n_multiple(width,n);
    crop(1,1,x*n,x*n);

    vector i_row;
    doubleVector ir_col;
    doubleVector ig_col;
    doubleVector ib_col;

    int half_length = (x*n)/2;

    i_row.resize(2*half_length,0);
    ir_col.resize(2*half_length,i_row);
    ig_col.resize(2*half_length,i_row);
    ib_col.resize(2*half_length,i_row);

    for(size_t i = 0; i < half_length; i++)
    {
        for(size_t j = 0; j < half_length; j++)
        {
            ir_col[i][j] = red[j+half_length/2][i+half_length/2];
            ig_col[i][j] = green[j+half_length/2][i+half_length/2];
            ib_col[i][j] = blue[j+half_length/2][i+half_length/2];
        }
    }

    vector row;
    doubleVector col;
    doubleVectorWrapper r_base;
    doubleVectorWrapper g_base;
    doubleVectorWrapper b_base;

    row.resize(x,0);
    col.resize(x,row);
    r_base.resize(x*x,col);
    g_base.resize(x*x,col);
    b_base.resize(x*x,col);

    for(size_t i = 0; i < x; i++)
    {
        for(size_t j = 0; j < x; j++)
        {
            fill_with_value(r_base[i*x+j],ir_col[i][j]);
            fill_with_value(g_base[i*x+j],ig_col[i][j]);
            fill_with_value(b_base[i*x+j],ib_col[i][j]);
        }
    }

    int k = 0;
    for(size_t j = x; j>= 1; j--)
    {
        for(size_t i = x; i >= 1; i--)
        {
                for(size_t p = 0; p < n; p++)
                {
                    for(size_t q = 0; q < n; q++)
                    {
                        red[(x-i)*n + p][(x-j)*n + q] = r_base[k][p][q];
                        green[(x-i)*n + p][(x-j)*n + q] = g_base[k][p][q];
                        blue[(x-i)*n + p][(x-j)*n + q] = b_base[k][p][q];
                    }
                }
        k++;
        }
    }

    pause();

}

void
Image::rmcolor()
{
    std::string color;
    vector z(width,0);

    printf("który kolor? [c]zerwony/[z]ielony/[n]iebieski\n");
    do
    {
        std::cin>>color;
    }while(color.length() != 1);

    if(color == "c")std::fill(red.begin(),red.end(),z);
    if(color == "z")std::fill(green.begin(),green.end(),z);
    if(color == "n")std::fill(blue.begin(),blue.end(),z);

    pause();
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

    x = round_to_n_multiple(width, n);
    y = round_to_n_multiple(height, n);

    crop(1,1,x*n,y*n);

    vector row;
    doubleVector col;
    doubleVectorWrapper r_base;
    doubleVectorWrapper g_base;
    doubleVectorWrapper b_base;

    row.resize(n,0);
    col.resize(n,row);
    r_base.resize(x*y,col);
    g_base.resize(x*y,col);
    b_base.resize(x*y,col);

    doubleVectorWrapper colors = {red, green, blue};
    tripleVectorWrapper base = {r_base, g_base, b_base};


    // Fisher-Yates
    srand(time(NULL));
    for (size_t i = 0; i < x*y; i++)
    {
        int j = i + rand() % (x*y - i);
        swap(r_base[i],r_base[j]);
        swap(g_base[i],g_base[j]);
        swap(b_base[i],b_base[j]);
    }

    colors_to_base(colors, base, x, y, n);

}

int
Image::round_to_n_multiple(int x, int n)
{
    return  (x - x % n) / n;
}

void
Image::pause()
{
    do
    {
        printf("Enter aby kontynuować.\n");
    } while (std::cin.get() != '\n');
}
void
Image::colors_to_base(doubleVectorWrapper &colors, tripleVectorWrapper &base, int x, int y, int n)
{
    int k=0;
    for(size_t o = 0; o < colors.size(); o++)
    {
        for(size_t j = x; j>= 1; j--)
        {
            for(size_t i = y; i >= 1; i--)
            {
                for(short int p = 0; p <= n-1; p++)
                {
                    for(short int q = 0; q <= n-1; q++)
                    {
                        colors[o][(y-i)*n + p][(x-j)*n + q] = base[o][k][p][q];
                    }
                }
                k++;
            }
        }
    }
}
void
Image::base_to_colors(tripleVectorWrapper &base, doubleVectorWrapper &colors, int x, int y, int n)
{
    int k=0;
    for(size_t o = 0; o < colors.size(); o++)
    {
        for(size_t j = x; j>= 1; j--)
        {
            for(size_t i = y; i >= 1; i--)
            {
                for(short int p = 0; p <= n-1; p++)
                {
                    for(short int q = 0; q <= n-1; q++)
                    {
                        base[o][k][p][q] = colors[o][(y-i)*n + p][(x-j)*n + q];
                    }
                }
                k++;
            }
        }
    }
}
