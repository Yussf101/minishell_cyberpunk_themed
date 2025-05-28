#include "cyber.h"

// Change directory
void builtin_cd(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "cd: missing argument\n");
    } else if (chdir(args[1]) != 0) {
        perror("cd failed");
    }
}

// Print working directory
void builtin_pwd(void) {
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
    } else {
        perror("pwd failed");
    }
}

// Clear screen
void builtin_clear(void) {
    printf("\033[H\033[J"); // ANSI escape sequence to clear screen
}