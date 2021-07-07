// Data types
#include "../my_string/my_string.h"
#include "../vector/vector.h"
#include "./node.h"

Status linked_list_insert_word(Node** pHead, MY_STRING key_name, MY_STRING current);
void linked_list_destroy(Node** pHead);
void linked_list_print(Node* head);
Boolean linked_list_assign_new_wf(Node* head, G_VECTOR current_wf, MY_STRING current_key);