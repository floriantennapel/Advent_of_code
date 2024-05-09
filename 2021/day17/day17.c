#include <stdio.h>

#define X_MIN 248
#define X_MAX 285
#define Y_MIN -85
#define Y_MAX -56

const int xMinV = 22; // smallest value with triangle number larger than X_MIN
const int xMaxV = X_MAX;
const int yMinV = Y_MIN;
const int yMaxV = (Y_MIN * (Y_MIN - 1)) / 2 + Y_MIN;

int withinTarget(int* pos) {
  return (pos[0] >= X_MIN) && (pos[0] <= X_MAX) &&
         (pos[1] >= Y_MIN) && (pos[1] <= Y_MAX);
}

int validShot(int* velocity) {
  int d_x = velocity[0];
  int d_y = velocity[1];
  int pos[] = {d_x, d_y};

  while (pos[0] <= X_MAX && pos[1] >= Y_MIN) {
    if (withinTarget(pos)) {
      return 1;
    }

    d_x = d_x != 0 ? d_x - 1 : 0;
    --d_y;

    pos[0] += d_x;
    pos[1] += d_y;
  }

  return 0;
}

int part2() {
  int sum = 0;

  for (int x = xMinV; x <= xMaxV; x++) {
    for (int y = yMinV; y <= yMaxV; y++) {
      int shot[] = {x, y};
      if (validShot(shot)) {
        ++sum;
      }
    }
  }

  return sum;
}

int main() {
  printf("part 1: %d\n", yMaxV);
  printf("part 2: %d\n", part2());
}
