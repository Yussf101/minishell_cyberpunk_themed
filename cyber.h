#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sysexits.h>

// Constants
#define MAX_INPUT 1024
#define MAX_ARGS 64
#define PATH_MAX 4096

// ANSI Color Codes
#define NEON_PINK   "\033[1;35m"
#define NEON_CYAN   "\033[1;36m"
#define NEON_PURPLE "\033[1;34m"
#define NEON_GREEN  "\033[1;32m"
#define NEON_RED    "\033[1;31m"
#define RST         "\033[0m"

// Utility Macros
#define ERROR(msg) fprintf(stderr, NEON_RED msg RST "\n")

// Function Prototypes
void printbanner(void);
void cyberpunkExit(void);
char *get_prompt(void);
char *read_line(void);
int parse_line(char *line, char **args, int *background);
void execute_command(char **args, int background);
int contains_pipe(char **args);
void execute_pipeline(char **args);
int check_redirection(char **args, char **input_file, char **output_file);
pid_t Fork(void);
void Execvp(const char *file, char *const argv[]);
void *Malloc(size_t size);

// Built-in Commands
void builtin_cd(char **args);
void builtin_pwd(void);
void builtin_clear(void);

#endif