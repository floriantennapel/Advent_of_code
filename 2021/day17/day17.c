#include <stdio.h>

const int xMin = 248;
const int xMax = 285;
const int yMin = -85;
const int yMax = -56;

const int xMinV = 22; // smallest value with triangle number larger than xMin
const int xMaxV = xMax;
const int yMinV = yMin;
const int yMaxV = (yMin * (yMin - 1)) / 2 + yMin;

int withinTarget(int* pos) {
  return (pos[0] >= xMin) && (pos[0] <= xMax) &&
         (pos[1] >= yMin) && (pos[1] <= yMax);
}

int validShot(int* velocity) {
  int d_x = velocity[0];
  int d_y = velocity[1];
  int pos[] = {d_x, d_y};

  while (pos[0] <= xMax && pos[1] >= yMin) {
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
