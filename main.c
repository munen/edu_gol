#include <stdlib.h>
#include <stdio.h>

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


_Bool create_world(world_t *world) {
  int i;

  // allocate memory to hold all lines in the world
  world->cells = (cell_t **) malloc(sizeof (cell_t *) * height);

  // for each line in the world, assign memory to it
  for(i = 0; i<=height; i++) {
    if(!(world->cells[i] = (cell_t *) malloc(sizeof(cell_t *) * width)))
      return false;
  }

  return true;
}


int main(int argc, char *argv[]) {
  if(!optparse(argc, argv))
        abort();

  world_t world;

  if(!create_world(&world))
    printf("error creating world\n");
  else
    printf("created world\n");
  
  return 0;
}
