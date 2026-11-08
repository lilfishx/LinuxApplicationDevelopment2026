#include <stdio.h>
#include <string.h>

#include <libintl.h>
#include <locale.h>

#include "config.h"

#define _(STRING) gettext(STRING)

#define PACKAGE "guess"

#ifndef LOCALEDIR
#define LOCALEDIR "/usr/local/share/locale"
#endif


#define START 1
#define END 100

int main() {
  int start = START;
  int end = END;
  int mid;
  char answer[32];


  
  setlocale(LC_ALL, "");
  bindtextdomain(PACKAGE, LOCALEDIR);
  textdomain(PACKAGE);

  printf(_("Pick a number %d to %d\n"), start, end);

  while (start != end) {
    mid = (start + end) / 2;

    printf(_("Is picked number greater then %d\n"), mid);

    if (fgets(answer, sizeof(answer), stdin) == NULL) {
      if (feof(stdin)) {
        printf(_("Stream ended: EOF reached with no data read.\n"));
        clearerr(stdin);
        continue;
      } else if (ferror(stdin)) {
        printf(_("An input error occurred.\n"));
      }
    }

    if (!strcmp(answer, _("Yes\n"))) {
      start = mid + 1;
    } else if (!strcmp(answer, _("No\n"))) {
      end = mid;
    } else {
      printf(_("Please answer 'Yes' or 'No'\n"));
    }
  }

  printf(_("You picked %d\n"), start);

}