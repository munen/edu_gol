#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

// return random value
_Bool true_or_false() {
  return (rand() % 2) ? true : false;
}

void randomize_world(world_t *world) {
  int i, j;
  // initialize randomizer for later use
  srand ( time(NULL) );

  // assign each cell random aliveness
  for(i = 0; i<height; i++) {
    for(j = 0; j<width; j++) {
      world->cells[i][j].alive = true_or_false();
    }
  }
}

void print_world(world_t *world) {
  int i, j;

  // print x-axis
  printf("  ");
  for(i = 0; i<width; i++)
    printf("%i", i);
  printf("  → x\n");

  // print each line
  for(i = 0; i<height; i++) {
    // print y-axis
    printf("%i ", i);
    // print cells
    for(j = 0; j<width; j++) {
      printf("%s", (world->cells[i][j].alive ? "▆": " "));
    }
    printf("\n");
  }
  printf("↓\ny\n");
}

_Bool read_world(world_t *world, char *path) {
  long file_size = 0;
  FILE *fp;
  char *input = NULL;

  fp = fopen(path, "r");

  // get filesize
  fseek(fp, 0L, SEEK_END);
  file_size = ftell(fp);
  fseek(fp, 0L, SEEK_SET);

  // read file
  input = (char *)malloc(sizeof(char) * file_size);
  fread(input, file_size, sizeof(char), fp);

  // note: there is no syntax checking
  width = strstr(input, "\n") - input;
  // account newlines (+1)
  height = (file_size) / (width + 1);

  create_world(world);

  int i, j, tmp = 0;
  for(i = 0; i<height; i++) {
    for(j = 0; j<width; j++) {
      world->cells[i][j].alive = (input[tmp] == '*') ? true : false;
      tmp += 1;
    }
    tmp += 1;
  }

  return true;
}

// returns number of living neighbours for any given cell coordinate
int neighbours(world_t *world, int y, int x) {
  int count = 0;

  // ... y-1 -1<x>1
  // .*. x-1 x+1
  // ... y+1 -1<x>1
  //
  // edge cases(pun intended):
  //   y = 0, y = height
  //   x = 0, x = width

  // above
  if(y > 0) {
    if(x > 0)
      count += world->cells[y-1][x-1].alive? 1 : 0;
    count += world->cells[y-1][x].alive? 1 : 0;
    if(x < width-1)
      count += world->cells[y-1][x+1].alive? 1 : 0;
  }

  // below
  if(y < height-1) {
    if(x > 0)
      count += world->cells[y+1][x-1].alive? 1 : 0;
    count += world->cells[y+1][x].alive? 1 : 0;
    if(x < width-1)
      count += world->cells[y+1][x+1].alive? 1 : 0;
  }

  // left
  if(x > 0)
    count += world->cells[y][x-1].alive? 1 : 0;

  // right
  if(x < width-1)
    count += world->cells[y][x+1].alive? 1 : 0;

  return count;
}

// show debug information: neighbour count for all cells
void show_neighbour_count(world_t *world) {
  int i, j;
  for(i = 0; i<height; i++) {
    for(j = 0; j<width; j++) {
      printf("neighbours of y(%i):x(%i) -> %i\n", i, j, neighbours(world, i, j));
    }
  }
}


int main(int argc, char *argv[]) {
  if(!optparse(argc, argv))
    exit(-1);

  world_t world;

  if(path)
    read_world(&world, path);
  else if (!create_world(&world)) {
    printf("error creating world\n");
    exit(-2);
  } 
  else {
    randomize_world(&world);
  }
  print_world(&world);
  show_neighbour_count(&world);

  return 0;
}
