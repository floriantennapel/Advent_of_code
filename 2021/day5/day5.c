#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define INPUT_LEN 500
#define MAX_LINE_LEN 20
#define FILE_NAME "in.txt"
#define GRID_DIM 1000 // biggest coordinate in input is 989

typedef void (*operation)(int*);
typedef bool (*condition)(int, int);

int lines[INPUT_LEN][4];

void readInput() {
  FILE* file = fopen(FILE_NAME, "r");
  if (file == NULL) {
    perror("Could not open file");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < INPUT_LEN; i++) {
    char line[MAX_LINE_LEN];
    if (fgets(line, MAX_LINE_LEN, file) == NULL) {
      perror("error reading line");
      exit(EXIT_FAILURE);
    }

    // sorry, I can't be bothered error checking strtok and atoi properly 
    // this will do
    lines[i][0] = atoi(strtok(line, ","));
    lines[i][1] = atoi(strtok(NULL, " ")); // there is probably a better way to skip the " -> "
    strtok(NULL, " ");
    lines[i][2] = atoi(strtok(NULL, ","));
    lines[i][3] = atoi(strtok(NULL, ""));
  }

  if (fclose(file) == EOF) {
    perror("Could not close file");
    exit(EXIT_FAILURE);
  }
}

void inc(int* x) {
  *x = *x + 1;
}

void dec(int* x) {
  *x = *x - 1;
}

bool le(int a, int b) {
  return a <= b;
}

bool ge(int a, int b) {
  return a >= b;
}

void drawDiagonalLine(int grid[GRID_DIM][GRID_DIM], int* line) {
  int x1 = line[0];
  int x2 = line[2];
  int y1 = line[1];
  int y2 = line[3];

  operation xOp = x1 < x2 ? inc : dec;
  operation yOp;
  condition yCond;

  if (y1 < y2) {
    yOp = inc;
    yCond = le;
  } else {
    yOp = dec;
    yCond = ge;
  }

  int x = x1;
  for (int y = y1; yCond(y, y2); yOp(&y)) {
    grid[y][x] += 1;
    xOp(&x);
  }
}


void drawLines(int grid[GRID_DIM][GRID_DIM], bool part2) {
  for (int i = 0; i < GRID_DIM; i++) {
    memset(grid[i], 0, GRID_DIM * sizeof(int)); 
  }

  for (int i = 0; i < INPUT_LEN; i++) {
    int* line = lines[i];

    if (line[0] == line[2]) {
      int lo;
      int hi;

      if (line[1] < line[3]) {
        lo = line[1];
        hi = line[3];
      } else {
        lo = line[3];
        hi = line[1];
      }

      for (int j = lo; j <= hi; j++) {
        grid[j][line[0]] += 1;
      }
    } else if (line[1] == line[3]) {
      int lo;
      int hi;

      if (line[0] < line[2]) {
        lo = line[0];
        hi = line[2];
      } else {
        lo = line[2];
        hi = line[0];
      }

      for (int j = lo; j <= hi; j++) {
        grid[line[1]][j] += 1;
      }
    } else if (part2) {
      drawDiagonalLine(grid, line);
    }
  }
}

int countOverlaps(int grid[GRID_DIM][GRID_DIM]) {
  int counter = 0;

  for (int i = 0; i < GRID_DIM; i++) {
    for (int j = 0; j < GRID_DIM; j++) {
      if (grid[i][j] > 1) {
        ++counter;
      }
    }
  }

  return counter;
}

int part1() {
  int grid[GRID_DIM][GRID_DIM];
  
  drawLines(grid, false);
  return countOverlaps(grid);
}

int part2() {
  int grid[GRID_DIM][GRID_DIM];

  drawLines(grid, true);
  return countOverlaps(grid);
}

int main() {
  readInput(); 
  
  printf("part1: %d\n", part1());
  printf("part2: %d\n", part2());

  return EXIT_SUCCESS; 
}
