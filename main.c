#include <stdlib.h>

#include "optparse.h"

int height, width = 0;
char *path        = NULL;

int main(int argc, char *argv[]) {
  if(!optparse(argc, argv))
        abort();
  return 0;
}
