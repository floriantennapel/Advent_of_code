#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROWS 137 
#define COLS 139 
#define FILE_NAME "in.txt"

typedef enum {NONE, VERT, HOR} Cucumber;

void readInput(Cucumber map[][COLS]) {
  FILE* file = fopen(FILE_NAME, "r");
  if (!file) {
    perror("readInput: ");
    exit(1);
  }

  char line[COLS + 2];
  for (int i = 0; i < ROWS; i++) {
    fgets(line, COLS + 2, file);

    for (int j = 0; j < COLS; j++) {
      char c = line[j];
      map[i][j] = c == '.' ? NONE : (c == '>' ? VERT : HOR);
    }
  }

  fclose(file);
} 
 
int stepCucumbers(Cucumber map[][COLS], int moveVert) {
  Cucumber* schedule[ROWS][COLS]; 
  memset(schedule, 0, sizeof(schedule));

  int count = 0;

  // setting schedule
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      Cucumber current = map[i][j];
      int shouldMove = moveVert ? current == VERT : current == HOR;
      Cucumber* next = moveVert ? &(map[i][(j + 1) % COLS]) : &(map[(i+1) % ROWS][j]);

      if (shouldMove && *next == NONE) {
        schedule[i][j] = next;
        ++count;
      }
    }
  }
  
  // moving according to schedule
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      if (schedule[i][j]) {
        *(schedule[i][j]) = map[i][j]; 
        map[i][j] = NONE;
      }
    }
  }

  // repeating for downwards moving cucumbers
  if (moveVert) {
    count += stepCucumbers(map, 0);
  }

  return count;
}

int part1(Cucumber map[][COLS]) {
  int step;
  for (step = 1; stepCucumbers(map, 1); step++) {}
  return step;
}

int main() {
  Cucumber map[ROWS][COLS]; 
  readInput(map);

  printf("part1: %d\n", part1(map));
}


