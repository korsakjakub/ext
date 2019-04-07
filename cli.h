#ifndef CLI_H
#define CLI_H

#include <sys/ioctl.h>
#include <stdio.h>
#include "image.h"

void run_cli(Image &image);
int get_terminal_width(struct winsize w);
int get_terminal_height(struct winsize w);
void draw_menu(int width);
void draw_line(int width);
void crop_image(char answer, int width, int height);
void clear_shell();
int clean_stdin();

#endif /* CLI_H */
