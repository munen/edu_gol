#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

#include "optparse.h"

void usage() {
  printf("valid arguments: -w (width) -h (height) -f (filename)\n");
}

/* Retrieves height, width and pathname
 * Writes instructions when user arguments are inconsistent */
_Bool optparse(int argc, char *argv[]) {
  int index;
  int c;

  opterr = 0;

  if(argc == 1) {
    usage();
    return false;
  }

  while ((c = getopt (argc, argv, "h:w:f:")) != -1)
    switch (c)
    {
      case 'h':
        height = atoi(optarg);
        break;
      case 'w':
        width = atoi(optarg);
        break;
      case 'f':
        path = optarg;
        break;
      case '?':
        if ((optopt == 'f') || (optopt == 'h') || (optopt == 'w'))
          fprintf (stderr, "Option -%c requires an argument.\n", optopt);
        else if (isprint (optopt))
          fprintf (stderr, "Unknown option `-%c'.\n", optopt);
        else
          fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
        return false;
      default:
	exit(-1);
    }

  for (index = optind; index < argc; index++)
    printf ("Non-option argument %s\n", argv[index]);

  if(path && (width && height)) {
    printf("Not using given width and height since you also gave an input file.\n");
    width  = 0;
    height = 0;
  }

  return true;
}
