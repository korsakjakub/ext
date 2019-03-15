#include "cli.h"

void run_cli(int width, int height)
{
    struct winsize w;

    printf("Rozmiar zdjęcia:\t szerokośc = %d\t wysokość = %d\n",width, height);

    int answer;

    while(1)
    {
        printf("Przyciąć? [y]/[n]\n");
        answer = getchar();
        if(answer == 'n' || answer == 'y') break;
    }
    if(answer == 'y')
    {
        int x,y;
        printf("x,y = ");
        scanf("%d,%d", &x, &y);
        printf("x = %d, y = %d\n",x,y);
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
