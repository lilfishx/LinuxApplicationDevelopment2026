#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <rhash.h>

#include "config.h"

// #define HAVE_LIBREADLINE 1

#ifdef HAVE_LIBREADLINE
#include <readline/readline.h>
#include <readline/history.h>
#endif

#define MAX_DIGEST_SIZE 128
#define MAX_OUTPUT_SIZE 256

int main() {
  char * line = NULL;
  size_t n = 0;

  char * hash = NULL;
  char * arg = NULL;
  char * msg;
  
  char output[MAX_OUTPUT_SIZE];
  unsigned char digest[MAX_DIGEST_SIZE];

  char base64_output = 0;
  unsigned int hash_id = 0;
  int flags;
  

  rhash_library_init();

  while (1) {

    errno = 0;
    hash_id = 0;
    hash = NULL;
    arg = NULL;
    
    #ifdef HAVE_LIBREADLINE
      line = readline("> ");
      if (!line) {
        if (line) {
          free(line);
        }
        return 0;
      }
    #else
      fprintf(stdout, "> ");

      if (getline(&line, &n, stdin) < 0) {
        // got eof
        if (!errno) {
          if (line) {
            free(line);
          }
          return 0;
        } else {
          if (line) {
            free(line);
          }
          perror("Error getline");
          return 1;
        }
      }
    #endif

    hash = strtok(line, " \n");
    if (!hash) {
      fprintf(stderr, "Cant parse first argument\n");
      free(line);
      line = NULL;
      continue;
    }

    arg = strtok(NULL, " \n");
    if (!arg) {
      fprintf(stderr, "Cant parse second argument\n");
      free(line);
      line = NULL;
      continue;
    }

    // fprintf(stdout, "Got args: %s %s\n", hash, arg);

    if (!strcmp(hash, "md5")) {
      base64_output = 1;
      hash_id = RHASH_MD5;
    }
    if (!strcmp(hash, "MD5")) {
      base64_output = 0;
      hash_id = RHASH_MD5;
    }

    if (!strcmp(hash, "sha1")) {
      base64_output = 1;
      hash_id = RHASH_SHA1;
    }
    if (!strcmp(hash, "SHA1")) {
      base64_output = 0;
      hash_id = RHASH_SHA1;
    }

    if (!strcmp(hash, "tth")) {
      base64_output = 1;
      hash_id = RHASH_TTH;
    }
    if (!strcmp(hash, "TTH")) {
      base64_output = 0;
      hash_id = RHASH_TTH;
    }

    if (!hash_id) {
      fprintf(stderr, "Command not supported\n");
      free(line);
      line = NULL;
      continue;
    }

    if (base64_output) {
      flags = RHPR_BASE64;
    } else {
      flags =  (RHPR_HEX | RHPR_UPPERCASE);
    } 

    if (arg[0] == '"') {
      msg = arg + 1;
      if (rhash_msg(hash_id, msg, strlen(msg), digest) < 0) {
        fprintf(stderr, "Message digest calculation error\n");
        free(line);
        line = NULL;
        continue;
      } 
    }
    else {
      if (rhash_file(hash_id, arg, digest) < 0) {
        fprintf(stderr, "File digest calculation error for \"%s\": %s\n", arg, strerror(errno));
        free(line);
        line = NULL;
        continue;
      }
    }
    
    rhash_print_bytes(output, digest, rhash_get_digest_size(hash_id), flags);
    output[strlen(output)] = '\0';

    fprintf(stdout, "%s\n", output);

    free(line);
    line = NULL;
    n = 0;

  }

}