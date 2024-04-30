#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_LEN 200
#define MAX_LINE_LEN 150
#define FILE_NAME "in.txt"

void readInput(char lines[][14][10]) {
  FILE* file = fopen(FILE_NAME, "r");
  if (file == NULL) {
    perror("");
    exit(EXIT_FAILURE);
  }
  
  for (int i = 0; i < INPUT_LEN; i++) {
    char line[MAX_LINE_LEN];
    if (fgets(line, MAX_LINE_LEN, file) == NULL) {
      perror("");
      exit(EXIT_FAILURE);
    }

    // first call to strtok must be separated
    strcpy(lines[i][0], strtok(line, " "));

    for (int j = 1; j < 15; j++) {
      char* s = strtok(NULL, " ");
      if (j < 10) {
        strcpy(lines[i][j], s);
      } else if (j > 10) {
        strcpy(lines[i][j-1], s);
      }
    }
  }

  fclose(file);
}

int part1(char lines[][14][10]) {
  int sum = 0;

  for (int i = 0; i < INPUT_LEN; i++) {
    for (int j = 10; j < 14; j++) {
      int len = strlen(lines[i][j]);
      if (j == 13) {
        --len;
      }

      if (len == 2 || len == 3 || len == 4 || len == 7) {
        sum += 1;
      }
    }
  }

  return sum;
}

int main() {
  char input[INPUT_LEN][14][10];
  readInput(input);

  printf("part1: %d\n", part1(input));

  return 0;
}
