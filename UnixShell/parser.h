#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "shell.h"
#include "execute_cmd.h"

int parse_command(char command[]);
void trim_string(char* string);
void remove_newline_from_input_stream();
char** split_string(char string[], char split_val, int amount_args);
int split_string_len(char string[], char split_val);
void free_args(char** args, int len);