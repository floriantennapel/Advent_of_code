#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INPUT_LEN 1000
#define MAX_LINE_LEN 11
#define FILE_NAME "in.txt"

typedef struct {
  bool vert; // is the movement vertical or horizontal
  int units;
} Move;

void readInput(Move* arr) {
  FILE* file = fopen(FILE_NAME, "r");

  for (int i = 0; i < INPUT_LEN; i++) {
    char buffer[MAX_LINE_LEN];
    fgets(buffer, MAX_LINE_LEN, file);

    Move currentMove;

    switch (buffer[0]) {
      case 'f':
        currentMove.vert = false; 
        currentMove.units = buffer[8] - '0'; // every move is given as single digit
        break;
      case 'u':
        currentMove.vert = true;
        currentMove.units = '0' - buffer[3]; // instead of keeping track of up and down, up is simply negative vertical movement
        break;
      case 'd':
        currentMove.vert = true;
        currentMove.units = buffer[5] - '0';
    }

    arr[i] = currentMove;
  }

  if (fclose(file) == EOF) {
    fprintf(stderr, "could not close file\n");
    exit(EXIT_FAILURE);
  }
}

long part1(Move* lines) {
  int depth = 0;
  int horizontal = 0;

  for (int i = 0; i < INPUT_LEN; i++) {
    Move move = lines[i];

    if (move.vert) {
      depth += move.units;
    } else {
      horizontal += move.units;
    }
  }

  return depth * horizontal; 
}

long part2(Move* lines) {
  int depth = 0;
  int horizontal = 0;
  int aim = 0;

  for (int i = 0; i < INPUT_LEN; i++) {
    Move move = lines[i];

    if (move.vert) {
      aim += move.units;
    } else {
      horizontal += move.units;
      depth += aim * move.units;
    }
  }


  return depth * horizontal;
}

int main() {
  Move lines[INPUT_LEN];
  readInput(lines);

  printf("part1: %ld\n", part1(lines));
  printf("part2: %ld\n", part2(lines));

  return EXIT_SUCCESS;
}
