#include <stdlib.h>

#include "optparse.h"

int height, width = 0;
char *path        = NULL;

typedef struct cell_t_ {
  _Bool alive;
  _Bool alive_next_round;
} cell_t;

typedef struct world_t_ {
  cell_t **cells;
} world_t;

int main(int argc, char *argv[]) {
  if(!optparse(argc, argv))
        abort();
  return 0;
}
