#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define INPUT_LEN 1000 
#define LINE_LEN 13 // 12 bits + \0 
#define FILE_NAME "in.txt"

void readInput(char lines[][LINE_LEN]) {
  FILE* file = fopen(FILE_NAME, "r");
  if (file == NULL) {
    fprintf(stderr, "Could not open file\n");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < INPUT_LEN; i++) {
    fgets(lines[i], LINE_LEN + 1, file);
    lines[i][LINE_LEN - 1] = '\0';
  }

  if (fclose(file) == EOF) {
    fprintf(stderr, "Could not close file\n");
    exit(EXIT_FAILURE);
  }
}

long part1(char lines[][LINE_LEN]) {
  // c has methods to convert binary string to long 
  // this is why gamma and epsilon are char[] and not bool[]
  char gamma[LINE_LEN];
  char epsilon[LINE_LEN];

  gamma[LINE_LEN - 1] = '\0';
  epsilon[LINE_LEN - 1] = '\0';

  int commonBits[LINE_LEN - 1];
  memset(commonBits, 0, (LINE_LEN-1) * sizeof(int));

  // counting 
  for (int i = 0; i < INPUT_LEN; i++) {
    char* line = lines[i];
    
    for (int j = 0; j < LINE_LEN - 1; j++) {
      commonBits[j] += line[j] - '0' ? 1 : -1;
    }
  }

  for (int i = 0; i < LINE_LEN - 1; i++) {
    char gammaVal = commonBits[i] >= 0 ? '1' : '0';
    gamma[i] = gammaVal;
    epsilon[i] = !(gammaVal - '0') + '0';
  }

  char* endptr = ""; // strtol needs this, I don't know why
  return strtol(gamma, &endptr, 2) * strtol(epsilon, &endptr, 2);
}

bool mostCommon(char lines[][LINE_LEN], bool validLines[], int index) {
  int count = 0;

  for (int i = 0; i < INPUT_LEN; i++) {
    if (!validLines[i]) {
      continue;
    }

    count += lines[i][index] - '0' ? 1 : -1;
  }

  return count >= 0;
}


long part2(char lines[][LINE_LEN]) {
  bool oxyValidLines[INPUT_LEN];
  bool co2ValidLines[INPUT_LEN];

  int oxygenIndex = -1;
  int co2Index = -1;

  memset(oxyValidLines, true, INPUT_LEN * sizeof(bool));
  memset(co2ValidLines, true, INPUT_LEN * sizeof(bool));

  for (int i = 0; i < LINE_LEN - 1; i++) {
    bool oxyMostCommon = mostCommon(lines, oxyValidLines, i);
    bool co2MostCommon = mostCommon(lines, co2ValidLines, i);

    int oxyCount = 0;
    int co2Count = 0;

    int lastOxyIndex;
    int lastCo2Index;

    for (int j = 0; j < INPUT_LEN; j++) {
      if (oxyValidLines[j] && oxygenIndex == -1) {
        if (oxyMostCommon == lines[j][i] - '0') {
          ++oxyCount;
          lastOxyIndex = j;
        } else {
          oxyValidLines[j] = false;
        }
      } 
      if (co2ValidLines[j] && co2Index == -1) {
        if (co2MostCommon != lines[j][i] - '0') {
          ++co2Count;
          lastCo2Index = j;
        } else {
          co2ValidLines[j] = false;
        }
      } 
    }

    if (oxyCount == 1) {
      oxygenIndex = lastOxyIndex;
    }
    if (co2Count == 1) {
      co2Index = lastCo2Index;
    }
  } 

  char* endptr = "";
  return strtol(lines[oxygenIndex], &endptr, 2) * strtol(lines[co2Index], &endptr, 2);
}


int main() {
  char lines[INPUT_LEN][LINE_LEN];
  readInput(lines);

  printf("part1: %ld\n", part1(lines));
  printf("part2: %ld\n", part2(lines));

  return EXIT_SUCCESS;
}
