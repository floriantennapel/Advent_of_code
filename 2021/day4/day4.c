#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INPUT_LEN 599
#define MAX_LINE_LEN 16
#define BOARD_DIM 5
#define NUMBERS_LEN 100 
#define FILE_NAME "in.txt"
#define NUMBER_OF_BOARDS (INPUT_LEN + 1) / (BOARD_DIM + 1) 

typedef struct {
  int score;
  int steps; // how many numbers where drawn before bingo
} BingoScore;

typedef struct {
  int board[BOARD_DIM][BOARD_DIM];
  bool checked[BOARD_DIM][BOARD_DIM];
} BingoBoard;

typedef struct {
  int row;
  int col;
} BoardPos;

int bingoNumbers[] = {69,88,67,56,53,97,46,29,37,51,3,93,92,78,41,22,45,66,13,82,2,7,52,40,18,70,32,95,89,64,84,68,83,26,43,0,61,36,57,34,80,39,6,63,72,98,21,54,23,28,65,16,76,11,20,33,96,4,10,25,30,19,90,24,55,91,15,8,71,99,58,14,60,48,44,17,47,85,74,87,86,27,42,38,81,79,94,73,12,5,77,35,9,62,50,31,49,59,75,1};

BoardPos findNumber(BingoBoard* bingoBoard, int number) {
  int row = -1;
  int col = -1;
  BoardPos pos;

  for (int i = 0; i < BOARD_DIM; i++) {
    for (int j = 0; j < BOARD_DIM; j++) {
      if (bingoBoard->board[i][j] == number) {
        row = i;
        col = j;
        bingoBoard->checked[i][j] = true;
      }    
    }
  }

  pos.row = row;
  pos.col = col;

  return pos;
}

bool isBingo(BingoBoard bingoBoard) {
  for (int i = 0; i < BOARD_DIM; i++) {
    int rowCount = 0;
    int colCount = 0;

    for (int j = 0; j < BOARD_DIM; j++) {
      if (bingoBoard.checked[i][j]) {
        ++rowCount;
      }
      if (bingoBoard.checked[j][i]) {
        ++colCount;
      }
    }

    if (rowCount == BOARD_DIM || colCount == BOARD_DIM) {
      return true;
    }
  }

  return false;
}

int calculateScore(BingoBoard bingoBoard, int lastNumber) {
  int sum = 0;

  for (int i = 0; i < BOARD_DIM; i++) {
    for (int j = 0; j < BOARD_DIM; j++) {
      if (!bingoBoard.checked[i][j]) {
        sum += bingoBoard.board[i][j];
      }
    }
  }

  return lastNumber * sum;
}

BingoScore checkBoard(BingoBoard bingoBoard) {
  BingoScore score = { .score = 0, .steps = NUMBERS_LEN + 1 }; 

  for (int i = 0; i < NUMBERS_LEN; i++) {
    int currentNum = bingoNumbers[i];

    BoardPos pos = findNumber(&bingoBoard, currentNum);

    // number was not found on board
    if (pos.row == -1) {
      continue;
    }

    if (isBingo(bingoBoard)) {
      score.score = calculateScore(bingoBoard, currentNum);
      score.steps = i+1;
      break;
    }
  }

  return score; 
}

void readInput(BingoBoard boards[NUMBER_OF_BOARDS]) {
  FILE* file = fopen(FILE_NAME, "r");
  if (file == NULL) {
    perror("Could not open file");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < NUMBER_OF_BOARDS; i++) {     
    BingoBoard bingoBoard;

    for (int j = 0; j < BOARD_DIM; j++) {
      char line[MAX_LINE_LEN];
      fgets(line, MAX_LINE_LEN, file);

      for (int k = 0; k < BOARD_DIM; k++) {
        bingoBoard.board[j][k] = atoi(line + k * 3); 
        bingoBoard.checked[j][k] = false;
      }
    }

    boards[i] = bingoBoard;

    // parse empty line
    char dummy[MAX_LINE_LEN];
    fgets(dummy, MAX_LINE_LEN, file);
  }

  if (fclose(file) == EOF) {
    perror("Could not close file");
    exit(EXIT_FAILURE);
  }
}

int part1(BingoBoard boards[NUMBER_OF_BOARDS]) {
  BingoScore winning = { .score = 0, .steps = NUMBERS_LEN + 1 };
 
  for (int i = 0; i < NUMBER_OF_BOARDS; i++) {
    BingoScore currentScore = checkBoard(boards[i]); 
    if (currentScore.steps < winning.steps) {
      winning = currentScore;
    }
  }

  return winning.score;
}

int part2(BingoBoard boards[NUMBER_OF_BOARDS]) {
  BingoScore last = { .score = 0, .steps = 0 };

  for (int i = 0; i < NUMBER_OF_BOARDS; i++) {
    BingoScore currentScore = checkBoard(boards[i]); 
    if (currentScore.steps > last.steps) {
      last = currentScore;
    }
  }

  return last.score;
}

int main() {
  BingoBoard boards[NUMBER_OF_BOARDS];
  readInput(boards);
  
  printf("part1: %d\n", part1(boards));
  printf("part2: %d\n", part2(boards));

  return EXIT_SUCCESS;
}
