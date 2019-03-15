#ifndef CLI_H
#define CLI_H

#include <sys/ioctl.h>
#include <stdio.h>

void run_cli();
int get_terminal_width(struct winsize w);
int get_terminal_height(struct winsize w);
void draw_line(int width);

#endif /* CLI_H */
