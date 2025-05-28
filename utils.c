#include "cyber.h"

pid_t Fork(void) {
    pid_t pid = fork();
    if (pid == -1) {
        perror(NEON_RED "fork failed" RST);
        exit(EXIT_FAILURE);
    }
    return pid;
}

void Execvp(const char *file, char *const argv[]) {
    if (!file || !argv) {
        fprintf(stderr, NEON_RED "Execvp: invalid arguments\n" RST);
        exit(EXIT_FAILURE);
    }
    if (execvp(file, argv) == -1) {
        perror(NEON_RED "execvp failed" RST);
        exit(EXIT_FAILURE);
    }
}

void *Malloc(size_t size) {
    void *ptr = malloc(size);
    if (!ptr) {
        perror(NEON_RED "malloc failed" RST);
        exit(EXIT_FAILURE);
    }
    return ptr;
}


#include <unistd.h>
#include <pwd.h>

char *get_prompt(void) {
    static char prompt[PATH_MAX + 100];
    char cwd[PATH_MAX];
    char *user = getpwuid(getuid())->pw_name;
    if (!getcwd(cwd, sizeof(cwd))) {
        perror("getcwd failed");
        return NULL;
    }
    snprintf(prompt, sizeof(prompt),
             NEON_PINK "NETRUNNER" NEON_CYAN "[%s]" NEON_PINK "> " RST,
             cwd);
    return prompt;
}