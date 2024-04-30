#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>

#define INPUT_LEN 94
#define MAX_LINE_LEN 150
#define FILE_NAME "in.txt"


int cmp(const void *a, const void *b) {
  long compared = (*(long*)a - *(long*)b);
  // I don't trust that the cast to int won't overflow
  return compared <= 0 ? (compared == 0 ? 0 : -1) : 1;
}

void readInput(char lines[][MAX_LINE_LEN]) {
  FILE* file = fopen(FILE_NAME, "r");
  if (file == NULL) {
    perror("");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < INPUT_LEN; i++) {
    if (fgets(lines[i], MAX_LINE_LEN, file) == NULL) {
      perror("");
      exit(EXIT_FAILURE);
    }
  }

  fclose(file);
}

long findError(char* str, bool part1) {
  int vals[] = {3, 57, 1197, 25137};
  char* openBr = "([{<";
  int stackSize = 100;

  int top = -1;
  char lastPopped;
  char stack[stackSize];

  for (int j = 0; j < MAX_LINE_LEN; j++) {
    char current = str[j];
    
    if (current == '\0') {
      break;
    }
    
    if (strchr(openBr, current) != NULL) {
      ++top;
      stack[top] = current; 

      if (top >= stackSize - 1) {
        fprintf(stderr, "stack overflow\n");
        exit(EXIT_FAILURE);
      }
    } else {
      char popped = stack[top]; 
      lastPopped = popped;
      --top;

      switch (current) {
        case ')':
          if (popped != '(') {
            return part1 ? vals[0] : -1;
          }
          break;
        case ']':
          if (popped != '[') {
            return part1 ? vals[1] : -1;
          }
          break;
        case '}':
          if (popped != '{') {
            return part1 ? vals[2] : -1;
          }
          break;
        case '>':
          if (popped != '<') {
            return part1 ? vals[3] : -1;
          }
          break;
      }
    }
  }

  if (part1) {
    return 0;
  } else {
    long score = 0;
    for (int i = top+1; i >= 0; i--) {
      score *= 5; 
      switch (stack[i]) {
        case '(':
          score += 1;
          break;
        case '[':
          score += 2;
          break;
        case '{':
          score += 3;
          break;
        case '<':
          score += 4;
          break;
      }
    }

    return score;
  }
}

int part1(char lines[][MAX_LINE_LEN]) { 
  int sum = 0;

  for (int i = 0; i < INPUT_LEN; i++) {
    sum += findError(lines[i], true);
  }

  return sum;
}

long part2(char lines[][MAX_LINE_LEN]) {
  long scores[INPUT_LEN];

  int n = 0;
  for (int i = 0; i < INPUT_LEN; i++) {
    long result = findError(lines[i], false);
    if (result != -1) {
      scores[n] = result;
      ++n;
    }
  }

  qsort(scores, n, sizeof(long), cmp);
  return scores[n / 2];
}

int main() {
  char input[INPUT_LEN][MAX_LINE_LEN];
  readInput(input);

  printf("part1: %d\n", part1(input));
  printf("part2: %ld\n", part2(input));
}
