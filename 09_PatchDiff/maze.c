#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 6
#define WALL '#'
#define PASS '.'

char **alloc_maze(int n) {
  char **maze = malloc(n * sizeof(*maze));
  for (int i = 0; i < n; i++) {
    maze[i] = malloc(n * sizeof(**maze));
  }
  return maze;
}

void free_maze(char **maze, int n) {
  for (int i = 0; i < n; i++) {
    free(maze[i]);
  }
  free(maze);
}

void init_maze(char **maze, int size) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (i % 2 == 0 || j % 2 == 0) {
        maze[i][j] = WALL;
      } else {
        maze[i][j] = PASS;
      }
    }
  }
}

void shuffle(int *arr, int n) {
  for (int i = n - 1; i > 0; i--) {
    int j = rand() % (i + 1);
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
  }
}

void generate(char **maze, int n) {
  const int dx[4] = { 0, 0, -1, 1 };
  const int dy[4] = { -1, 1, 0, 0 };

  int *stack_x = malloc(n * n * sizeof(*stack_x));
  int *stack_y = malloc(n * n * sizeof(*stack_y));
  int *visited = calloc(n * n, sizeof(*visited));
  int order[4];
  int stack_top = 0;

  stack_x[stack_top] = 0;
  stack_y[stack_top] = 0;
  visited[0] = 1;

  while (stack_top >= 0) {
    int cx = stack_x[stack_top];
    int cy = stack_y[stack_top];

    for (int i = 0; i < 4; i++) {
      order[i] = i;
    }
    shuffle(order, 4);

    int moved = 0;
    for (int i = 0; i < 4; i++) {
      int dir = order[i];
      int nx = cx + dx[dir];
      int ny = cy + dy[dir];

      if (nx < 0 || nx >= n || ny < 0 || ny >= n) {
        continue;
      }
      if (visited[ny * n + nx]) {
        continue;
      }

      maze[cy * 2 + 1 + dy[dir]][cx * 2 + 1 + dx[dir]] = PASS;
      visited[ny * n + nx] = 1;

      stack_top++;
      stack_x[stack_top] = nx;
      stack_y[stack_top] = ny;
      moved = 1;
      break;
    }

    if (!moved) {
      stack_top--;
    }
  }

  free(stack_x);
  free(stack_y);
  free(visited);
}

void print_maze(char **maze, int size) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      putchar(maze[i][j]);
    }
    putchar('\n');
  }
}

int main(void) {
  int size = N * 2 + 1;
  char **maze;

  srand(time(NULL));

  maze = alloc_maze(size);
  init_maze(maze, size);
  generate(maze, N);
  print_maze(maze, size);
  free_maze(maze, size);

  return 0;
}
