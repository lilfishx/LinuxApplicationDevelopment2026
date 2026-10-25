#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>


int main(int argc, char *argv[]) {
  int fd;
  struct stat st;
  size_t size;
  char *infile;
  char *outfile;
  char *buf;

  errno = 0; 

  if (argc < 2 || argc > 3) {
		printf(
      "Usage:\n"
      "\t./move INFILE OUTFILE\n"
    );
    return 1;
  }

  infile = argv[1];
  outfile = argv[2];

  if (stat(infile, &st)) {
    perror("Error stat infile");
    return 2;
  }
  size = st.st_size;

  if (!S_ISREG(st.st_mode)) {
    printf("Error %s is not a regular file\n", infile);
    return 3;
  }

  fd = open(infile, O_RDONLY, 0);
  if (fd < 0) {
    perror("Error open infile");
    return 4;
  }

  buf = malloc(size);
  if (!buf) { 
    printf("Error malloc");
    close(fd);
    return 5;
  } 

  if (read(fd, buf, size) < 0) { 
    free(buf); 
    close(fd);
    perror("Error read infile");
    return 6; 
  }

  close(fd);

  remove(outfile);

  fd = open(outfile, O_WRONLY | O_CREAT, st.st_mode);
  if (fd < 0) {
    free(buf);
    perror("Error open outfile");
    return 8;
  }

  if (write(fd, buf, size) < 0) {
    close(fd);
    remove(outfile);
    free(buf);
    perror("Error write outfile");
    return 9;
  }

  close(fd);

  if (remove(infile) < 0) {
    free(buf);
    perror("Error remove infile");
    return 10;
  }

  free(buf);
  return 0;
}