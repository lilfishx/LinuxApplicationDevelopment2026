#define _GNU_SOURCE
#include <dlfcn.h>
#include <string.h>

typedef int (*remove_type)(char *);

int remove(char * filename) {
  int res;
  
  if (strstr(filename, "PROTECT")) {
    return 0;
  }

  return ((remove_type)(dlsym(RTLD_NEXT, "remove")))(filename);
}