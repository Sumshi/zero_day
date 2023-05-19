#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <limits.h>
#include <signal.h>
#include <fcntl.h>
#include<stdbool.h>
#include <stdarg.h>
#define BUFFER_SIZE 1024
#define MAX_ARGS 100
extern char **environ;

int clear();
void printPrompt();
void parseInput(char *buffer, char **args);
char *getAbsolutePath(char *command);
void executeCommand(char *cmd, char **args);
void printEnv();
int changeDirectory(char *directory);
int mySetEnv(char *var, char *value);
int myUnsetEnv(char *var);

int handleAnd(char *input);
int handleOr(char *input);
/*functions used prototypes*/
char **tokenize(char *str, char *delimiter);
unsigned int _strlen(char *str);
char *_strcpy(char *dest, char *src);
char *_strtok(char *str, const char *delim);
unsigned int check_match(char c, const char *str);
char *_strcat(char *dest, const char *src);
int _strcmpr(char *strcmp1, char *strcmp2);
char *_strdup(char *strtodup);
size_t _strcspn(const char *str1, const char *str2);
int _strncmp(const char *str1, const char *str2, size_t n);
int _atoi(char *str);
int _snprintf(char *str, size_t size, const char *format, ...);
int _sprintf(char *str, const char *format, ...);
#endif
