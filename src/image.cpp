#include "image.h"
#include "colors.h"

#include <iostream>
#include <algorithm>
#include <fstream>

Image::Image (std::string input)
{
    vector t_red;
    vector t_green;
    vector t_blue;
    int k = 0;

    std::string temp = "";
    int x = 0, color = 0, y=0;

    for(auto & c : input){
        //accumulate integer
        if (c >= 48 && c <= 57){ //check if c is an integer (ASCII table)
            temp += c;
        }else{
            if(temp != ""){
                int o = std::stoi(temp);
                if(k <= 3){
                    switch(k){
                        case 0: type = o;
                                break;
                        case 1: width = o;
                                t_red.resize(width,0);
                                t_green.resize(width,0);
                                t_blue.resize(width,0);
                                break;
                        case 2: height = o;
                                red.resize(height,t_red);
                                green.resize(height,t_green);
                                blue.resize(height,t_blue);
                                break;
                        case 3: color_depth = o;
                                break;
                    }
                    ++k;
                }else if(type == 3){

                    switch(color % 3)
                    {
                        case 0: t_red[x] = o;break;
                        case 1: t_green[x] = o; break;
                        case 2: t_blue[x] = o;x++;break;
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

                }else if(type == 2){
                    t_red[x] = o;
                    x++;
                    if (x == width)
                    {
                        red[y] = t_red;
                        x = 0;
                        y++;
                    }
                }
            }
            temp.clear();
        }
    }
}

int Image::get_width() {return width;}

int Image::get_height() {return height;}

int Image::get_color_depth() {return color_depth;}

int Image::get_type() { return type; }// 50 - pgm, 51 - ppm

void Image::write()
{
    std::string file_path;
    do{
        std::cout<<"Podaj nazwę pliku: (bez rozszerzenia)\n";
        std::cin>>file_path;
    }while(file_path.empty());

    if( type == 3)
    {
    std::ofstream output_file("output/" + file_path + ".ppm");
    output_file <<"P"<< type <<"\n" << width << " " << height << "\n" <<color_depth << "\n";
        for(size_t j = 0; j < height; j++)
        {
            for(size_t i = 0; i < width; i++)
            {
                output_file << red[j][i] << "\n" << green[j][i] << "\n" <<  blue[j][i] <<"\n";
            }
        }
    } else if (type == 2)
    {
        std::ofstream output_file("output/" + file_path + ".pgm");
        output_file << "P"<< type <<"\n" << width << " " << height << "\n" <<color_depth << "\n";
        for(size_t j = 0; j < height; j++)
        {
            for(size_t i = 0; i < width; i++)
            {
                output_file << red[j][i] << "\n";
            }
        }
    }
    std::cout<<"Zapisano pomyślnie.\n";
    pause();
}

std::string Image::to_string()
{
    std::string output = "";
    if(get_type() == 3)//ppm
    {
        for (size_t i = 0; i < height; i++)
        {
            for (size_t j = 0; j < width; j++)
            {
                output.append(std::to_string(red[i][j]));
                output.append("\n");
                output.append(std::to_string(green[i][j]));
                output.append("\n");
                output.append(std::to_string(blue[i][j]));
                output.append("\n");
            }
        }
    } else if (get_type() == 2)//pgm
    {
        for (size_t i = 0; i < height; i++)
        {
            for (size_t j = 0; j < width; j++)
            {
                output.append(std::to_string(red[i][j]));
                output.append("\n");
            }
        }
    }
    return output;
}

void Image::crop(int x1, int y1, int x2, int y2)
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

void Image::flip(char orientation)
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

void Image::fill_with_value(doubleVector &arr, short int value)
{
    for(size_t i = 0; i < arr.size(); i++)
    {
        for(size_t j = 0; j < arr.size(); j++)
        {
            arr[i][j] = value;
        }
    }
}

int Image::round_to_n_multiple(int x, int n)
{
    return  (x - x % n);
}

void Image::zoom()
{
    int n=1, x, y;

    while(1)
    {
        std::cout<<"podaj n: ";
        std::cin>>n;
        if(n <= 1 || n >= width || n >= height || height/n <= n || width/n <= n){
            continue;
        }
        break;
    }

    x = round_to_n_multiple(width,n);
    crop(1,1,x,x);

    vector row;
    doubleVector col;
    doubleVectorWrapper r_base;
    doubleVectorWrapper g_base;
    doubleVectorWrapper b_base;

    row.resize(n,0);
    col.resize(n,row);
    r_base.resize(x*x/n/n,col);
    g_base.resize(x*x/n/n,col);
    b_base.resize(x*x/n/n,col);

    for(size_t i = 0; i < x/n; i++)
    {
        for(size_t j = 0; j < x/n; j++)
        {
            fill_with_value(r_base[i*x/n+j],red[j+x/n][i+x/n]);
            fill_with_value(g_base[i*x/n+j],green[j+x/n][i+x/n]);
            fill_with_value(b_base[i*x/n+j],blue[j+x/n][i+x/n]);
        }
    }

    int k = 0;
    for(size_t j = x/n; j>= 1; j--)
    {
        for(size_t i = x/n; i >= 1; i--)
        {
                for(size_t p = 0; p < n; p++)
                {
                    for(size_t q = 0; q < n; q++)
                    {
                        red[x-i*n + p][x-j*n + q] = r_base[k][p][q];
                        green[x-i*n + p][x-j*n + q] = g_base[k][p][q];
                        blue[x-i*n + p][x-j*n + q] = b_base[k][p][q];
                    }
                }
        k++;
        }
    }

    printf("3\n");
    pause();

}

void Image::rmcolor()
{
    std::string color;
    vector z(width,0);

    std::cout<<"który kolor? [c]zerwony/[z]ielony/[n]iebieski\n";
    do
    {
        std::cin>>color;
    }while(color.length() != 1);

    if(color == "c")std::fill(red.begin(),red.end(),z);
    if(color == "z")std::fill(green.begin(),green.end(),z);
    if(color == "n")std::fill(blue.begin(),blue.end(),z);

    pause();
}

void Image::puzzle()
{
    int n, x,y;

    while(1)
    {
        std::cout<<"podaj n: ";
        scanf("%d", &n);

        if (n > width || n > height)
        {
            std::cout<<"n jest za duże jak na to zdjęcie\n";
            continue;
        }
        break;
    }

    x = round_to_n_multiple(width, n);
    y = round_to_n_multiple(height, n);

    crop(1,1,x,y);

    vector row;
    doubleVector col;
    doubleVectorWrapper r_base;
    doubleVectorWrapper g_base;
    doubleVectorWrapper b_base;

    row.resize(n,0);
    col.resize(n,row);
    r_base.resize(x*y/n/n,col);
    g_base.resize(x*y/n/n,col);
    b_base.resize(x*y/n/n,col);

    int k=0;
        for(size_t j = x/n; j>= 1; j--)
        {
            for(size_t i = y/n; i >= 1; i--)
            {
                for(short int p = 0; p <= n-1; p++)
                {
                    for(short int q = 0; q <= n-1; q++)
                    {
                        r_base[k][p][q] = red[y-i*n + p][x-j*n + q];
                        g_base[k][p][q] = green[y-i*n + p][x-j*n + q];
                        b_base[k][p][q] = blue[y-i*n + p][x-j*n + q];
                        //printf("%d\t%d\t%d\n",r_base[k][p][q], g_base[k][p][q], b_base[k][p][q]);
                    }
                }
                k++;
            }
        }

    // Fisher-Yates
    srand(time(NULL));
    for (size_t i = 0; i < x*y/n/n; i++)
    {
        int j = i + rand() % (x*y/n/n - i);
        swap(r_base[i],r_base[j]);
        swap(g_base[i],g_base[j]);
        swap(b_base[i],b_base[j]);
    }

    k=0;
        for(size_t j = x/n; j>= 1; j--)
        {
            for(size_t i = y/n; i >= 1; i--)
            {
                for(short int p = 0; p <= n-1; p++)
                {
                    for(short int q = 0; q <= n-1; q++)
                    {
                        red[y-i*n + p][x-j*n + q] = r_base[k][p][q];
                        green[y-i*n + p][x-j*n + q] = g_base[k][p][q];
                        blue[y-i*n + p][x-j*n + q] = b_base[k][p][q];
                    }
                }
                k++;
            }
        }

}


void Image::pause()
{
    do
    {
        std::cout<<"Enter aby kontynuować.\n";
    } while (std::cin.get() != '\n');
}
