#include "cyber.h"

int contains_pipe(char **args) {
    for (int i = 0; args[i] != NULL; i++) {
        if (strcmp(args[i], "|") == 0)
            return 1;
    }
    return 0;
}

void execute_pipeline(char **args) {
    char *commands[16][MAX_ARGS];
    int cmd_count = 0;
    int arg_index = 0;
    int pipe_index = 0;

    while (args[arg_index] != NULL) {
        if (strcmp(args[arg_index], "|") == 0) {
            commands[cmd_count][pipe_index] = NULL;
            cmd_count++;
            pipe_index = 0;
        } else {
            commands[cmd_count][pipe_index++] = args[arg_index];
        }
        arg_index++;
    }
    commands[cmd_count][pipe_index] = NULL;
    cmd_count++;

    int pipefd[2], prev_fd = -1;
    for (int i = 0; i < cmd_count; i++) {
        if (i < cmd_count - 1 && pipe(pipefd) < 0) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if (pid == 0) {
            if (prev_fd != -1) {
                dup2(prev_fd, STDIN_FILENO);
                close(prev_fd);
            }
            if (i < cmd_count - 1) {
                close(pipefd[0]);
                dup2(pipefd[1], STDOUT_FILENO);
                close(pipefd[1]);
            }
            execvp(commands[i][0], commands[i]);
            perror("execvp failed");
            exit(EXIT_FAILURE);
        }
        if (prev_fd != -1) close(prev_fd);
        if (i < cmd_count - 1) {
            close(pipefd[1]);
            prev_fd = pipefd[0];
        }
    }
    for (int i = 0; i < cmd_count; i++) {
        wait(NULL);
    }
}

void execute_command(char **args, int background) {
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid == 0) {
        char *input_file = NULL;
        char *output_file = NULL;
        check_redirection(args, &input_file, &output_file);
        if (input_file) {
            int fd_in = open(input_file, O_RDONLY);
            if (fd_in < 0) {
                perror("Input redirection failed");
                exit(EXIT_FAILURE);
            }
            dup2(fd_in, STDIN_FILENO);
            close(fd_in);
        }
        if (output_file) {
            int fd_out = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd_out < 0) {
                perror("Output redirection failed");
                exit(EXIT_FAILURE);
            }
            dup2(fd_out, STDOUT_FILENO);
            close(fd_out);
        }
        execvp(args[0], args);
        perror("exec failed");
        exit(EXIT_FAILURE);
    } else {
        if (!background) {
            waitpid(pid, NULL, 0);
        } else {
            printf("[background pid: %d]\n", pid);
        }
    }
}

int check_redirection(char **args, char **input_file, char **output_file) {
    int i = 0;
    *input_file = NULL;
    *output_file = NULL;
    while (args[i] != NULL) {
        if (strcmp(args[i], "<") == 0 && args[i + 1]) {
            *input_file = args[i + 1];
            args[i] = NULL;
            i++;
        } else if (strcmp(args[i], ">") == 0 && args[i + 1]) {
            *output_file = args[i + 1];
            args[i] = NULL;
            i++;
        }
        i++;
    }
    return 0;
}