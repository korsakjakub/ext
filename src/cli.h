#ifndef CLI_H
#define CLI_H

#include <sys/ioctl.h>
#include <cstdio>
#include "image.h"

class TerminalInterface {
    public:
        void run_cli(Image &image);
        int get_terminal_width();
        int get_terminal_height();
        void set_width(int w);
        void set_height(int h);
        void draw_menu(int width, int img_width, int img_height);
        void draw_line(int width);
        void crop_image(Image &image, int width, int height);
        void clear_shell();
        int clean_stdin();
    private:
        int width;
        int height;
};


#endif /* CLI_H */
