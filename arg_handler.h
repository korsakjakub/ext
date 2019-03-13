#ifndef ARG_HANDLER_H
#define ARG_HANDLER_H

#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

void remove_element(char *array, int index, int amount, int array_length);
void remove_comments(char *string);

#endif /* ARG_HANDLER_H */
