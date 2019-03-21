#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>

int main(int argc, char *argv[]) {
  int base, status;
  char *str, *endptr;
  long id;
  if(argc < 2) {
    fprintf(stderr, "Usage: %s hostid [base]\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  str = argv[1];
  base = (argc > 2) ? atoi(argv[2]) : 16;
  errno = 0;
  id = strtol(str, &endptr, base);
  if ((errno == ERANGE && (id == LONG_MAX || id == LONG_MIN)) || (errno != 0 && id == 0)) {
    perror("strtol");
    exit(EXIT_FAILURE);
  }
  if (endptr == str) {
    fprintf(stderr, "No digits were found\n");
    exit(EXIT_FAILURE);
  }
  status = sethostid(id);
  if(status == 0) fprintf(stdout, "Host id changed to 0x%x\n", id);
  else {
    perror("sethostid");
    exit(EXIT_FAILURE);
  }
  return 0;
}
