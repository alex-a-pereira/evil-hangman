#ifndef ASSOC_ARR_H
#define ASSOC_ARR_H

#include "status.h"

typedef void* NODE_MY_STR;

struct map_t * map_create ();

void map_set (struct map_t *m, char *name, int value);

int map_get (struct map_t *m, char *name);

void map_destroy (struct map_t *m);

#endif
