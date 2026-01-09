#ifndef SHELL_H
#define SHELL_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

void execute_command(char **args, char *prog_name, int line_num);
int main(int argc, char **argv);
char *find_path(char *command);
char *find_path(char *command);
int main(int argc, char **argv);
void exec(char **args);
int main(int argc, char **argv);

#endif
