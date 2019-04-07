#ifndef CLI_H
#define CLI_H

#include <sys/ioctl.h>
#include <stdio.h>
#include "image.h"

void run_cli(Image &image);
int get_terminal_width(struct winsize w);
int get_terminal_height(struct winsize w);
void draw_line(int width);

#endif /* CLI_H */
