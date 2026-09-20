#include <curses.h>

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>

#define DX 7
#define DY 3


int get_file_content(char *filename, char **buf, char ***lines, size_t *count) {
  int fd;
  struct stat st;
  size_t size;

  *count = 0;
  if (stat(filename, &st)) {
    return -1;
  }
  size = st.st_size;

  fd = open(filename, O_RDONLY, 0);
  if (fd < 0) {
    return -1;
  }

  *buf = malloc(size + 1);
  if (!*buf) { 
    close(fd); 
    return -1;
  } 
  
  if (read(fd, *buf, size) < 0) { 
    free(*buf); close(fd);
    return -1; 
  }
  close(fd);

  (*buf)[size] = 0;

  for (size_t i = 0; i < size; i++) {
    if ((*buf)[i] == '\n') {
      *count += 1;
    }
  }
  if (size > 0 && (*buf)[size - 1] != '\n') {
    *count += 1;
  }

  if (*count == 0) {
    return 0;
  }

  *lines = malloc(*count * sizeof(char *));
  if (!*lines) { 
    free(*buf);
    return -1;
  }

  size_t j = 0;
  char *start = *buf;
  for (size_t i = 0; i < size; i++) {
    if ((*buf)[i] == '\n') {
      (*buf)[i] = 0;
      (*lines)[j++] = start;
      start = *buf + i + 1;
    }
  }
  if (start < *buf + size) {
    (*lines)[j++] = start;
  }

  return 0;
}


int render(WINDOW *win, size_t row, size_t col, char **lines, size_t count) {
  int max_y, max_x;
  getmaxyx(win, max_y, max_x);
  
  werase(win);

  for (int i = 0; i < max_y; i++) {
    size_t line_idx = row + i;
    if (line_idx >= count) {
      break;
    }

    char *current_line = lines[line_idx];
    size_t line_len = strlen(current_line);

    if (line_len > col) {
      mvwaddnstr(win, i, 0, current_line + col, max_x);
    }
  }

  wrefresh(win);
  return 0;
}


int main (int argc, char* argv[]) {
  WINDOW *win, *frame;
  char *filename;
  char *buf;
  char **lines;
  size_t count = 0;
  int c;
  size_t col = 0, row = 0;
  char *error = 0;
  
  if (argc < 2) {
    error = "Usage: ./Show <filename>\n";
    goto quit;
  }

  filename = argv[1];

  if (!initscr()) {
    error = "Error initialising ncurses.\n";
    goto quit;
  }

  if (cbreak()) {
    error = "Error setting cbreak.\n";
    goto free_scr;
  }

  if (noecho()) {
    error = "Error setting noecho.\n";
    goto free_scr;
  }

  frame = newwin(LINES - 2 * DY, COLS - 2 * DX, DY, DX);
  if (!frame) {
    error = "Error creating frame.\n";
    goto free_scr;
  }

  if (box(frame, 0, 0)) { 
    error = "Error creating boarder.\n";
    goto free_frame;
  }

  if (mvwaddstr(frame, 0, (COLS - 2 * DX - (int)strlen(filename)) / 2, filename)) {
    error = "Error printing filename to frame.\n";
    goto free_frame;
  }

  if (wrefresh(frame)) {
    error = "Error refreshing frame.\n";
    goto free_frame;
  }

  if (get_file_content(filename, &buf, &lines, &count)) {
    error = "Error getting file contents.\n";
    goto free_frame;
  }

  win = newwin(LINES - 2 * DY - 2, COLS - 2 * DX - 2, DY + 1, DX + 1);
  if (!win) {
    error = "Error creating window.\n";
    goto free_buf;
  }

  if (keypad(win, TRUE)) {
    error = "Error creating window.\n";
    goto free_buf;
  }

  if (scrollok(win, FALSE)) {
    error = "Error creating window.\n";
    goto free_buf;
  }

  if (render(win, row, col, lines, count)) {
    error = "Error rendering window.\n";
    goto free_all;
  }

  while((c = wgetch(win)) != 27) {

    if ((c == ' ' || c == KEY_DOWN) && row < count - 1) {
      row += 1;
    }

    if ((c == KEY_UP) && row > 0) {
      row -= 1;
    }

    if (c == KEY_RIGHT) {
      col += 1;
    }

    if (c == KEY_LEFT && col > 0) {
      col -= 1;
    }

    if (render(win, row, col, lines, count)) {
      error = "Error rendering window.\n";
      goto free_all;
    }
  }

free_all:
  if (delwin(win) != OK) {
    error = "Error freeing window.\n";
  }

free_buf:
  free(lines);
  free(buf);

free_frame:
  if (delwin(frame) != OK) {
    error = "Error freeing frame.\n";
  }
  
free_scr:
  if (endwin() != OK) {
    error = "Error freeing ncurses.\n";
  }

quit:
  if (error) {
    printf("%s\n", error);
    return -1;
  }
  return 0;
}
