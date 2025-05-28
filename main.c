#include "cyber.h"

// Entry animation
void printbanner(void) {
    const char *loading[] = {
        "⚡ SYSTEM BOOT UP INITIATED ⚡",
        "⚡ LAUNCHING PROCESSES..... ⚡",
        "⚡ CONNECTING TO MATRIX.....⚡",
        "⚡ WELCOME, NETRUNNER.         ⚡",
    };
    const int frames = sizeof(loading) / sizeof(loading[0]);

    printf(NEON_PINK "\n"
           " ____ _   _ ___  ____ ____ ___  _  _ _  _ _  _ \n"
           "|     \\_/  |__] |___ |__/ |__] |  | |\\ | |_/  \n"
           "|___   |   |__] |___ |  \\ |    |__| | \\| | \\_ \n"
           NEON_CYAN "                  WELCOME to CYBERSHELL\n"
           NEON_PURPLE "                     by_YousseFatimi\n" RST);

    for (int i = 0; i < frames; i++) {
        printf("\r" NEON_GREEN "%s" RST, loading[i]);
        fflush(stdout);
        usleep(200000);
    }
    printf("\n\n");
}

// Exit animation
void cyberpunkExit() {
    const char *shutdown[] = {
        "⚡ SYSTEM SHUTDOWN INITIATED ⚡",
        "⚡ TERMINATING PROCESSES...   ⚡",
        "⚡ DISCONNECTING FROM MATRIX...⚡",
        "⚡ GOODBYE, NETRUNNER.         ⚡",
    };
    const int frames = sizeof(shutdown) / sizeof(shutdown[0]);

    printf(NEON_RED "\n");
    for (int i = 0; i < frames; i++) {
        printf("\r" NEON_RED "%s" RST, shutdown[i]);
        fflush(stdout);
        usleep(500000);
    }
    printf("\n" NEON_CYAN "✅ EXIT COMPLETE ✅\n" RST);
    exit(0);
}

// Main function
int main() {
    char *line;
    char *args[MAX_ARGS];
    int background;

    printbanner(); // Display startup banner

    while (1) {
        line = readline(get_prompt());
        if (line && *line) {
            add_history(line);
        }
        if (line == NULL) {
            printf("\n");
            break;
        }

        if (strlen(line) == 0) {
            free(line);
            continue;
        }

        // Parse and execute
        parse_line(line, args, &background);

        // Built-in commands
        if (strcmp(args[0], "exit") == 0) {
            cyberpunkExit();
        } else if (strcmp(args[0], "cd") == 0) {
            builtin_cd(args);
        } else if (strcmp(args[0], "pwd") == 0) {
            builtin_pwd();
        } else if (strcmp(args[0], "clear") == 0) {
            builtin_clear();
        } else if (contains_pipe(args)) {
            execute_pipeline(args);
        } else {
            execute_command(args, background);
        }

        free(line);
    }

    return 0;
}