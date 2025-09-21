/* Name: lab2.c
 Description: program should receieve user input from keyboard
 input should be the full path of a program to run
 the command is then executed
 these steps are then repeated forever
 Requirements: Must use fork(), exec(), waitpid()
 Author: Alvin Kong
 Date: 2026/09/20
 */

#define _POSIX_C_SOURCE 200809L
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  char *userInput = NULL;
  size_t size = 0;
  char *savePtr = NULL;
  char *token = NULL;

  // program should loop forever
  while (true) {
    // prompt user for program path
    printf("Enter programs to run.\n> ");
    ssize_t returnVal = getline(&userInput, &size, stdin);
    if (returnVal == -1) {
      perror("Getline failed");
      free(userInput);
      exit(EXIT_FAILURE);
    }
    token = strtok_r(userInput, "\n", &savePtr);

    // fork, execute program
    pid_t checkPid = fork();
    if (checkPid) // is parent
    {
      int status = 0;
      if (waitpid(checkPid, &status, 0) == -1) {
        perror("Waitpid failed");
        free(userInput);
        exit(EXIT_FAILURE);
      }
    } else // is child
    {
      if (execl(token, token, (char *)NULL) == -1) {
        perror("Exec failed");
        exit(EXIT_FAILURE);
      }
    }

    free(userInput);
    userInput = NULL;
    size = 0;
  }
  return 0;
}
