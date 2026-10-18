#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char *argv[]) {
  long start = 0;
  long stop;
  long step = 1;
  char *endptr;

  errno = 0; 

  if (argc < 2 || argc > 4) {
    printf(
      "Usage:\n"
      "\t./range STOP\n"
      "\t./range START STOP [STEP]\n"
    );
    return 1;
  }

  if (argc == 2) {
    stop = strtol(argv[1], &endptr, 10);
    if (errno || argv[1] == endptr) {
      printf("Error converting stop to long");
      return 1;
    }
  }

  if (argc == 3) {
    start = strtol(argv[1], &endptr, 10);
    if (errno || argv[1] == endptr) {
      printf("Error converting start to long");
      return 1;
    }

    stop = strtol(argv[2], &endptr, 10);
    if (errno || argv[2] == endptr) {
      printf("Error converting stop to long");
      return 1;
    }
  }

  if (argc == 4) {
    start = strtol(argv[1], &endptr, 10);
    if (errno || argv[1] == endptr) {
      printf("Error converting start to long");
      return 1;
    }

    stop = strtol(argv[2], &endptr, 10);
    if (errno || argv[2] == endptr) {
      printf("Error converting stop to long");
      return 1;
    }

    step = strtol(argv[3], &endptr, 10);
    if (errno || argv[3] == endptr) {
      printf("Error converting step to long");
      return 1;
    }
  }

  for (long i = start; i < stop; i+=step) {
    printf("%ld\n", i);
  }

  return 0;
}