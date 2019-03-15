#!/bin/sh
tcc -o ext main.c arg_handler.c cli.c
./ext "testy/e3.ppm"
