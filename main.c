#include <stdlib.h>

#include "optparse.h"

int height, width = 0;
char *path        = NULL;

typedef struct {
  _Bool alive;
  _Bool alive_next_round;
} cell_t;

typedef struct {
  cell_t **cells;
} world_t;

int main(int argc, char *argv[]) {
  if(!optparse(argc, argv))
        abort();
  return 0;
}
