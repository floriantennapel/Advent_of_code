#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>

#define INPUT_LEN 94
#define MAX_LINE_LEN 150
#define FILE_NAME "in.txt"
#define STACK_SIZE 100

typedef struct {
  char arr[STACK_SIZE];
  char top;
} Stack;

void push(Stack *stack, char val) {
  if (stack->top >= STACK_SIZE) {
    fprintf(stderr, "stack overflow");
    exit(EXIT_FAILURE);
  }

  ++(stack->top);
  stack->arr[stack->top] = val; 
}

char pop(Stack *stack) {
  if (stack->top == -1) {
    return '\0';
  }

  --(stack->top);
  return stack->arr[stack->top + 1];
}

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
  Stack stack;
  stack.top = -1;

  char lastPopped;

  for (int j = 0; j < MAX_LINE_LEN; j++) {
    char current = str[j];
    
    if (current == '\0') {
      break;
    }
    
    if (strchr(openBr, current) != NULL) {
      push(&stack, current);
    } else {
      char popped = pop(&stack); 
      //lastPopped = popped;

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
    ++(stack.top); // a bit hacky, but it works
    char bracket;

    while ((bracket = pop(&stack)) != '\0') {
      score *= 5; 
      switch (bracket) {
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
