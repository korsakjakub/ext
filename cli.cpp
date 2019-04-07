#include "cli.h"
#include "image_operations.h"

int clean_stdin()
{
    while (getchar() !='\n');
    return 1;
}

void run_cli(Image &img)
{
    struct winsize w;
    int width = img.get_width();
    int height = img.get_height();
    int depth = img.get_color_depth();

    printf("Rozmiar zdjęcia:\t szerokośc = %d\t wysokość = %d\t głębia = %d\n",width, height, depth);

    int answer;

    while(1)
    {
        printf("Przyciąć? [y]/[n]\n");
        answer = getchar();
        if(answer == 'n' || answer == 'y') break;
    }
    if(answer == 'y')
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
                    x2 <= x1 || y2 <= y1 ||
                    x1 <= 0 ||  y1 <= 0
               );
    }


    draw_line(get_terminal_width(w));
    printf("Opcje:\n");
    printf("1. Odbijanie w pionie\n");
    printf("2. Odbijanie w poziomie\n");
    printf("3. Powiększanie n razy\n");
    printf("4. Pomniejszanie n razy\n");
    printf("5. Usunięcie danego koloru\n");
    printf("6. Puzzle\n");
    draw_line(get_terminal_width(w));
    while(1)
    {
        answer = getchar();
        switch(atoi(answer))
        {
            case 1: flip('v',img);
                    break;
            case 2: flip('h',img);
                    break;
            case 3: zoom('+',n,img);
                    break;
            case 4: zoom('-',n,img);
                    break;
            case 5: rmcolor(img);
                    break;
            case 6: puzzle(img);
                    break;
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
        printf("_");
    }
    printf("\n\n");
}
