#include "cli.h"
#include "stdlib.h"
#include "stdio.h"
#include "colors.h"

void run_cli(Image &img)
{
    struct winsize w;
    int width = img.get_width();
    int height = img.get_height();
    int depth = img.get_color_depth();
    int answer;

    printf("Rozmiar zdjęcia:\t szerokośc = %d\t wysokość = %d\t głębia = %d\n",width, height, depth);


    while(1)
    {
        printf("Przyciąć? [y]/[n]\n");
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
                     img.print();
                     draw_menu(get_terminal_width(w), img.get_width(), img.get_height());
        }

    }
}

int get_terminal_width(struct winsize w)
{
    ioctl(0, TIOCGWINSZ, &w);
    return w.ws_col;
}

int get_terminal_height(struct winsize w)
{
    ioctl(0, TIOCGWINSZ, &w);
    return w.ws_row;
}

void draw_line(int width)
{
    for (size_t i = 0; i < width; i++)
    {
        printf("%s_",YEL);
    }
    printf("%s\n\n",NRM);
}

void draw_menu(int width, int img_width, int img_height)
{
    draw_line(width);
    printf("%sOpcje:%s\n",CYN,NRM);
    printf("%s1.%s Odbijanie w pionie\n",RED, NRM);
    printf("%s2.%s Odbijanie w poziomie\n",RED, NRM);
    printf("%s3.%s Zoom n razy\n",RED, NRM);
    printf("%s4.%s Usunięcie danego koloru\n",RED,NRM);
    printf("%s5.%s Puzzle\n",RED,NRM);
    printf("%s6.%s Zapisz\n",RED,NRM);
    printf("szerokość: %d, wysokośc : %d\n", img_width, img_height);
    draw_line(width);
}

void crop_image(Image &img , int width, int height)
{
    int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
    char c;

    do
    {
        printf("x1,y1,x2,y2 = ");
    } while(
           (
                (scanf("%d,%d,%d,%d%c", &x1, &y1, &x2, &y2, &c) != 5 || c!='\n') && clean_stdin()) ||
                x1 > width || y1 > height ||
                x2 > width || y2 > height ||
                x2 < x1 || y2 < y1 ||
                x1 <= 0 ||  y1 <= 0
           );
    img.crop(x1,y1,x2,y2);
    printf("przycięto do (%d,%d),(%d,%d)\n",x1,y1,x2,y2);
}

void clear_shell() {
    // \x1B[2J clears screen, \x1B[H moves the cursor to top-left corner
    printf("\x1B[2J\x1B[H");
}

int
clean_stdin()
{
    while (getchar() !='\n');
    return 1;
}
