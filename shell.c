/*#include "main.h"
int main(void) {
    char buffer[BUFFER_SIZE];
    ssize_t length;
    pid_t pid;
    int status, i;
    char *args[MAX_ARGS + 1];
    int argCount = 0;
    char *token, *cmd;
    char *pathDirectory[MAX_ARGS + 1];
    int numDirectory = 0;

    while (1) {
        if (isatty(STDIN_FILENO) == 1)
            write(STDOUT_FILENO, "$ ", 2);

        length = read(STDIN_FILENO, buffer, BUFFER_SIZE);
        if (length == -1) {
            perror("Error from read");
            exit(EXIT_FAILURE);
        }
        if (length == 0) {
            break;
        }
        if (buffer[length - 1] == '\n') {
            buffer[length - 1] = '\0';
        }

        argCount = 0;
        token = strtok(buffer, " ");
        while (token != NULL) {
            args[argCount++] = token;
            if (argCount >= MAX_ARGS) {
                break;
            }
            token = strtok(NULL, " ");
        }
        args[argCount] = NULL;

        if (args[0][0] == '/') {
            // Command contains absolute path
            cmd = strdup(args[0]);
        } else {
            // Command is a relative/short name, search in PATH directories
            char *pathEnvVar = getenv("PATH");
            token = strtok(pathEnvVar, ":");
            while (token != NULL) {
                pathDirectory[numDirectory++] = token;
                if (numDirectory >= MAX_ARGS) {
                    break;
                }
                token = strtok(NULL, ":");
            }
            pathDirectory[numDirectory] = NULL;

            cmd = NULL;
            for (i = 0; i < numDirectory; i++) {
                char tempCmd[BUFFER_SIZE];
                snprintf(tempCmd, BUFFER_SIZE, "%s/%s", pathDirectory[i], args[0]);
                if (access(tempCmd, X_OK) == 0) {
                    cmd = strdup(tempCmd);
                    break;
                }
            }
        }

        if (cmd == NULL) {
            printf("%s: command not found\n", args[0]);
            continue;
        }

        pid = fork();
        if (pid == -1) {
            perror("fork error");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            execve(cmd, args, NULL);
            perror("execve error");
            exit(EXIT_FAILURE);
        } else {
            waitpid(pid, &status, 0);
        }

        free(cmd);
    }

    return 0;
}*/
