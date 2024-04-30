#include <stdio.h>
#include <stdlib.h>

#define FILE_NAME "in.txt"
#define MAX_LINE_LEN 6
#define INPUT_LEN 2000

void readInput(int* lines) {
  FILE* file = fopen(FILE_NAME, "r");
  
  for (int i = 0; i < INPUT_LEN; i++) {
    char buffer[MAX_LINE_LEN];

    if (fgets(buffer, MAX_LINE_LEN, file) == NULL) {
      fprintf(stderr, "Could not read input\n");
      exit(EXIT_FAILURE);
    }

    int depth = atoi(buffer);
    if (depth == 0) {
      fprintf(stderr, "Could not convert line to integer, at i = %d\n", i);
      exit(EXIT_FAILURE);
    }

    lines[i] = depth;
  } 

  if (fclose(file) == EOF) {
    fprintf(stderr, "could not close file\n");
    exit(EXIT_FAILURE);
  }
}

int part1(int* lines) {
  int counter = 0;

  for (int i = 1; i < INPUT_LEN; i++) {
    if (lines[i] > lines[i-1]) {
      ++counter;
    }
  }

  return counter;
}

int part2(int* lines) {
  int counter = 0;

  for (int i = 1; i < INPUT_LEN - 2; i++) {
    int prev = lines[i-1] + lines[i] + lines[i+1];
    int current = lines[i] + lines[i+1] + lines[i+2];

    if (current > prev) {
      ++counter;
    }
  }

  return counter;
}

int main() {
  int lines[INPUT_LEN];
  readInput(lines);
  
  printf("part1: %d\n", part1(lines));
  printf("part2: %d\n", part2(lines));

  return EXIT_SUCCESS;
}

