/*
 * Filename: lab3.c
 * Description: program reads in user input from keyboard line by line
 *              each input can include spaces or other characters
 *              the last 5 lines of user inputs are stored
 *              user can enter command print (no arguments) to print the last 5
 * lines of user in put to thhe screen. print would then be the most recent user
 * input Author: Alvin Kong Date: 2025/09/26
 */
#define _POSIX_C_SOURCE 200809
#define arrSize 5
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cleanArr(char **arr) {
  for (int i = 0; i < arrSize; i++) {
    free(arr[arrSize]);
  }
  return;
}

char *getUserInput(char **arr) {
  char *userInput = NULL;
  size_t inputSize = 0;

  printf("Enter input: ");
  ssize_t returnVal = getline(&userInput, &inputSize, stdin);
  if (returnVal == -1) {
    perror("getline failed\n");
    cleanArr(arr);
    exit(EXIT_FAILURE);
  }
  return userInput;
}

void storeUserInput(char **arr, char **userInput, int *head) {
  *head = (*head + 1) % arrSize;
  free(arr[*head]);
  arr[*head] = *userInput;
  return;
}

int main() {
  // initialize variables
  char *inputHist[arrSize] = {0};
  int head = -1;
  int current = 0;
  int currentSize = 0;

  // program runs until user inputs CTRL+C
  while (1) {

    char *userInput = getUserInput(inputHist);
    storeUserInput(inputHist, &userInput, &head);
    if (currentSize < arrSize) {
      currentSize++;
    }
    if (strcmp(userInput, "print\n") == 0) {
      current = head;
      for (int i = 0; i < currentSize; i++) {
        printf("%s", inputHist[current]);
        current = (current - 1 + arrSize) % arrSize;
      }
    }
  }
  return 0;
}
