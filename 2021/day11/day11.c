#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "in.txt"
#define GRID_SIZE 10

typedef struct Octopus Octopus;

struct Octopus {
  bool hasFlashed;
  Octopus* adjacent[8];
  char energy;
};

void readInput(Octopus[][GRID_SIZE]);
int part1(Octopus[][GRID_SIZE]);
int part2(Octopus[][GRID_SIZE]);
int step(Octopus[][GRID_SIZE]);
int flash(Octopus*);
void getAdjacent(Octopus*, Octopus[][GRID_SIZE], int, int);


int main() {
  Octopus octopi[GRID_SIZE][GRID_SIZE];
  readInput(octopi);

  printf("part1: %d\n", part1(octopi));

  readInput(octopi); //resetting array after part 1
  printf("part2: %d\n", part2(octopi));

  return EXIT_SUCCESS;
}


void readInput(Octopus arr[][GRID_SIZE]) {
  FILE* file = fopen(FILE_NAME, "r");
  if (file == NULL) {
    perror("");
    exit(EXIT_FAILURE);
  }


  // initial read
  for (int i = 0; i < GRID_SIZE; i++) {
    char line[GRID_SIZE + 2];
    if (fgets(line, GRID_SIZE + 2, file) == NULL) {
      perror("");
      exit(EXIT_FAILURE);
    }

    for (int j = 0; j < GRID_SIZE; j++) {
      Octopus octopus;
      octopus.hasFlashed = false;
      octopus.energy = line[j] - '0';
      memset(octopus.adjacent, 0, sizeof(octopus.adjacent));
      arr[i][j] = octopus;
    }
  }

  // adding adjacencies
  for (int i = 0; i < GRID_SIZE; i++) {
    for (int j = 0; j < GRID_SIZE; j++) {
      getAdjacent(&(arr[i][j]), arr, i, j);
    }
  }
  
  fclose(file);
}


int part1(Octopus octopi[][GRID_SIZE]) {
  int count = 0;

  for (int i = 0; i < 100; i++) {
    int flashes = step(octopi);
    count += flashes;
  }

  return count;
}


int part2(Octopus octopi[][GRID_SIZE]) {
  for (int i = 1; ; i++) {
    if (step(octopi) == GRID_SIZE * GRID_SIZE) {
      return i;
    }
  }
}


int step(Octopus octopi[][GRID_SIZE]) {
  int flashes = 0;

  for (int i = 0; i < GRID_SIZE; i++) {
    for (int j = 0; j < GRID_SIZE; j++) {
      Octopus* octopus = &(octopi[i][j]); 
      ++(octopus->energy);
    }
  }

  for (int i = 0; i < GRID_SIZE; i++) {
    for (int j = 0; j < GRID_SIZE; j++) {
      Octopus* octopus = &(octopi[i][j]);

      if (octopus->energy > 9) {
        flashes += flash(octopus);
      }
    }
  }

  for (int i = 0; i < GRID_SIZE; i++) {
    for (int j = 0; j < GRID_SIZE; j++) {
      Octopus* octopus = &(octopi[i][j]);

      if (octopus->hasFlashed) {
        octopus->hasFlashed = false;
        octopus->energy = 0;
      }
    }
  }


  return flashes;
}


int flash(Octopus* octopus) {
  if (octopus->hasFlashed) {
    return 0;
  }

  int flashes = 1;

  octopus->hasFlashed = true;

  Octopus* adjacent;
  for (int i = 0; i < 8; i++) {
    if ((adjacent = octopus->adjacent[i]) == NULL) {
      break;
    }
    
    ++(adjacent->energy);
    if (adjacent->energy > 9) {
      flashes += flash(adjacent);
    }
  }

  return flashes;
}


void getAdjacent(Octopus* octopus, Octopus arr[][GRID_SIZE], int row, int col) {
  int max = GRID_SIZE - 1;

  int r1 = row == 0 ? 0 : row - 1;
  int r2 = row == max ? max : row + 1;
  int c1 = col == 0 ? 0 : col - 1;
  int c2 = col == max ? max : col + 1;

  int count = 0; 
  for (int i = r1; i <= r2; i++) {
    for (int j = c1; j <= c2; j++) {
      if (i == row && j == col) {
        continue;
      }

      octopus->adjacent[count++] = &(arr[i][j]);
    }
  }
}
