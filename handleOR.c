#include "main.h"
int handleOr(char *input) {
    int status;
    pid_t pid;
    char *args[MAX_ARGS];

     /* Split input string into separate arguments */
    int i = 0;
    char *token = strtok(input, " \t\n\r");
    while (token != NULL && i < MAX_ARGS - 1) {
        args[i] = token;
        token = strtok(NULL, " \t\n\r");

        /* Handle quoted strings */
        if (args[i][0] == '"' || args[i][0] == '\'') {
            char *end_quote = strchr(args[i] + 1, args[i][0]);
            if (end_quote != NULL) {
                end_quote[0] = '\0';
                memmove(args[i], args[i] + 1, strlen(args[i]));
            }
        }

        i++;
    }
    args[i] = NULL;

    /* Fork a new process */
    pid = fork();

    if (pid == 0) {
        /* Child process */
        execve(args[0], args, NULL);

        /* If execve returns, there was an error */
        perror("execve failed");
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        /* Fork failed */
        perror("fork failed");
        exit(EXIT_FAILURE);
    } else {
        /* Parent process */
       waitpid(pid, &status, 0);

       if (WIFEXITED(status) && WEXITSTATUS(status) != 0){
           return handleAnd(strtok(NULL, ""));
       } 
       else{
           return 1;
       }
    }
}
