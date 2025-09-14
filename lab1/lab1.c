/* Filename: lab1.c
 * Description: Program receives a full ine of user (keyboard) input, tokenizes
 * it with delimiter " " (space), and prints out each token one at a time on a
 * new line Author: Alvin Kong Date: 2025/09/14
 */

#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  // variable initialization
  char *userInput = NULL;
  char *savePtr = NULL;
  char *token = NULL;
  size_t size = 0;

  // receive and store user input
  printf("Please enter some text: ");
  ssize_t num_char = getline(&userInput, &size, stdin);
  // throw error if getline fails
  if (num_char == -1) {
    perror("getline failed");
    if (userInput != NULL) {
      free(userInput);
    }
    exit(EXIT_FAILURE);
  }

  // tokenize user input, print out each token
  for (char *inputInit = userInput;; inputInit = NULL) {
    token = strtok_r(inputInit, " ", &savePtr);
    if (token == NULL) {
      break;
    }
    printf("%s\n", token);
  }
  free(userInput);
  return 0;
}
