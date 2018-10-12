#include <stdio.h>
#include "my_string.h"
#include "status.h"
#include "vector.h"

typedef struct node_my_str Node_my_str;
struct node_my_str
{
  MY_STRING *key;
  GEN_VECTOR data; // gen vector of My_string objects
  Node_my_str *next;
};

NODE_MY_STR node_my_str_init_default (void)
{
  Node_my_str *pNode_my_str = NULL;
  pNode_my_str = (Node_my_str *) malloc (sizeof (Node_my_str));
  pNode_my_str->key = NULL;
  pNode_my_str->value = NULL;
  pNode_my_str->next = NULL;
  return pNode_my_str;
}

Status node_my_str_set_node (NODE_MY_STR hNode_my_str, My_string key, Gen_vector array)
{
  Map_my_str *pMap_my_str = (Map_my_str *)hMap_my_str;

  if (pMap_my_str->name == NULL)
    {
      pMap_my_str->name = (char *) malloc (strlen (name) + 1);
      my_string_assignment(pMap_my_str->key, key)
      strcpy (m->name, name);
      m->value = value;
      m->nxt = NULL;
      return;
    }
  for (map = m;; map = map->nxt)
    {
      if (!strcasecmp (name, map->name))
	{
	  if (map->value != NULL)
	    {
	      map->value = value;
	      return;
	    }
	}
      if (map->nxt == NULL)
	{
	  map->nxt = (struct map_t *) malloc (sizeof (struct map_t));
	  map = map->nxt;
	  map->name = (char *) malloc (strlen (name) + 1);
	  strcpy (map->name, name);
	  map->value = value;
	  map->nxt = NULL;
	  return;
	}
    }
}

int map_get (struct map_t *m, char *name)
{
  struct map_t *map;
  for (map = m; map != NULL; map = map->nxt)
    {
      if (!strcasecmp (name, map->name))
	{
	  return map->value;
	}
    }
  return -99;
}

void map_destroy (struct map_t *m)
{
  struct map_t *temp;
  while (m != NULL)
    {
      temp = m->nxt;
      printf ("Deleting node w/ key: %s\n", m->name);
      free (m->name);
      free (m);
      m = temp;
    }
}
