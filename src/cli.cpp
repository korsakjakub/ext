#include "cli.h"
#include "colors.h"
#include <iostream>

void TerminalInterface::run_cli(Image &img)
{
    int width = img.get_width();
    int height = img.get_height();
    int depth = img.get_color_depth();
    int answer;

    std::cout<<"Rozmiar zdjęcia:\t szerokośc = "<<width<<"\t wysokość = "<<height<<"\t głębia = "<<depth<<"\n";


    while(1)
    {
        std::cout<<"Przyciąć? [y]/[n]\n";
        answer = getchar();
        if(answer == 'n' || answer == 'y') break;
    }

    if(answer == 'y')
    {
        crop_image(img, width, height);
    }
    while(1)
    {
        answer = getchar();
        if(answer == 'q'){break;}

        switch(answer)
        {
            case '1': img.flip('v');
                    break;
            case '2': img.flip('h');
                    break;
            case '3': img.zoom();
                    break;
            case '4': img.rmcolor();
                    break;
            case '5': img.puzzle();
                    break;
            case '6': img.write();
                    break;
            default: clear_shell();
                     draw_menu(get_terminal_width(), img.get_width(), img.get_height());
        }

    }
}

int TerminalInterface::get_terminal_width()
{
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);
    return w.ws_col;
}

int TerminalInterface::get_terminal_height()
{
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);
    return w.ws_row;
}

void TerminalInterface::draw_line(int width)
{
    for (size_t i = 0; i < width; i++)
    {
        std::cout<<YEL<<"_";
    }
    std::cout<<NRM<<"\n\n";
}

void TerminalInterface::draw_menu(int width, int img_width, int img_height)
{
    draw_line(width);
    std::cout<<CYN<<"Opcje:\n";
    std::cout<<RED<<"1."<<NRM<<"Odbijanie w pionie\n";
    std::cout<<RED<<"2."<<NRM<<"Odbijanie w poziomie\n";
    std::cout<<RED<<"3."<<NRM<<"Zoom n razy\n";
    std::cout<<RED<<"4."<<NRM<<"Usunięcie danego koloru\n";
    std::cout<<RED<<"5."<<NRM<<"Puzzle\n";
    std::cout<<RED<<"6."<<NRM<<"Zapisz\n";
    std::cout<<RED<<"[q]"<<NRM" aby wyjść\n";
    std::cout<<"szerokość: "<<img_width<<", wysokość : "<<img_height<<"\n";
    draw_line(width);
}

void TerminalInterface::crop_image(Image &img , int width, int height)
{
    int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
    char c;

    do
    {
        std::cout<<"x1,y1,x2,y2 = ";
    } while(
           (
                (scanf("%d,%d,%d,%d%c", &x1, &y1, &x2, &y2, &c) != 5 || c!='\n') && clean_stdin()) ||
                x1 > width || y1 > height ||
                x2 > width || y2 > height ||
                x2 < x1 || y2 < y1 ||
                x1 <= 0 ||  y1 <= 0
           );
    img.crop(x1,y1,x2,y2);
    std::cout<<"przycięto do ("<<x1<<", "<<y1<<"),("<<x2<<", "<<y2<<")\n";
}

void TerminalInterface::clear_shell() {
    // \x1B[2J clears screen, \x1B[H moves the cursor to top-left corner
    std::cout<<"\x1B[2J\x1B[H";
}

int TerminalInterface::clean_stdin()
{
    while (getchar() !='\n');
    return 1;
}
