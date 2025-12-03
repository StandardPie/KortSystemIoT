#ifndef SAFE_INPUT_H
#define SAFE_INPUT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_int_input(const char* prompt);
void get_string_input(const char* prompt, char* buffer, size_t buffer_size );

#endif