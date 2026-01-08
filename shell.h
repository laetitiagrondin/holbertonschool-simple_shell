#ifndef SHELL_H
#define SHELL_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

void execute_command(char *cmd, char *prog_name);
int main(int argc, char **argv);
char *find_path(char *command);
char *find_path(char *command);
int main(void);
void exec(char **args);
int main(void);

#endif
