#ifndef ASSOC_ARR_H
#define ASSOC_ARR_H
#include "my_string.h"
#include "status.h"
#include "vector.h"
typedef void* NODE_MY_STR;
NODE_MY_STR node_my_str_init_default(void);

Status node_my_str_push_back(NODE_MY_STR hNode, MY_STRING hString_to_push);

void linked_list_destroy(NODE_MY_STR* phNode);
Status linked_list_push_back(NODE_MY_STR head, MY_STRING key, MY_STRING current_word);

Status linked_list_assign_new_wf(NODE_MY_STR head, MY_STRING hKey, GEN_VECTOR hWord_bank);
#endif
