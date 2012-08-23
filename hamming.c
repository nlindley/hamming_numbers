#include <stdio.h>
#include <stdlib.h>
#include "hamming.h"

int main(int argc, char **argv) {

  int terms = atoi(*(++argv));

  node *l_final = NULL;
  node *l_final_temp = NULL;
  node *l_temp = NULL;
  node *l_2 = NULL;
  node *l_3 = NULL;
  node *l_2_3_merge = NULL;
  node *l_5 = NULL;

  append_node(2, &l_temp);
  append_node(3, &l_temp);
  append_node(5, &l_temp);

  while (!has_enough_terms(l_final, l_temp, terms)) {
    l_2 = generate_terms(l_temp, 2);
    l_3 = generate_terms(l_temp, 3);
    l_5 = generate_terms(l_temp, 5);

    l_final_temp = l_final;
    l_final = merge_lists(l_temp, l_final);
    free_list(l_final_temp);
    l_final_temp = NULL;

    free_list(l_temp);
    l_2_3_merge = merge_lists(l_2, l_3);
    l_temp = merge_lists(l_2_3_merge, l_5);
    free_list(l_2);
    free_list(l_3);
    free_list(l_2_3_merge);
    free_list(l_5);
  }

  print_count_nodes(l_final, terms);

  free_list(l_temp);
  free_list(l_final);

  l_2 = NULL;
  l_3 = NULL;
  l_2_3_merge = NULL;
  l_5 = NULL;
  l_temp = NULL;
  l_final = NULL;
  l_final_temp = NULL;

  return 0;
}

void print_count_nodes(node *list, int count) {
  int i;
  rewind_list(&list);

  for (i = 0; i < count; ++i) {
    printf("[%d, %d]\n", i + 1, list->value);
    list = list->next;
  }
}


int has_enough_terms(node *final_list, node *temp_list, int terms) {
  node *tmp = temp_list;
  rewind_list(&tmp);
  int min_value = tmp->value;

  if (list_count(final_list) >= terms &&
      node_at_index(final_list, terms)->value <= min_value) {
    return 1;
  } else {
    return 0;
  }
}

node *node_at_index(node *final_list, int count) {
  int i;
  node *temp_list = final_list;

  rewind_list(&temp_list);

  for (i = 1; i < count; ++i) {
    temp_list = temp_list->next;
  }

  return temp_list;
}

int list_count(node *list) {
  int count = 0;

  rewind_list(&list);

  while (list) {
    count += 1;
    advance_list(&list);
  }

  return count;
}

void append_node(int value, node **list) {
  if (!*list) {
    *list = initialize_list(value);
  } else {

    fast_forward_list(list);

    (*list)->next = malloc(sizeof(node));
    (*list)->next->prev = *list;
    (*list) = (*list)->next;
    (*list)->value = value;
    (*list)->next = NULL;
  }
}

void free_list(node *list) {
  if (!list) return;
  rewind_list(&list);
  free_nodes(list);
}

void free_nodes(node *list) {
  node *current = list;

  while (current) {
    node *next = current->next;
    free(current);
    current = next;
  }
}

node *initialize_list(int value) {
  node *list = malloc(sizeof(node));
  list->value = value;
  list->next = NULL;
  list->prev = NULL;
  return list;
}

node *generate_terms(node *list, int multiplier) {
  node *current = list;
  node *new_list = NULL;

  rewind_list(&current);

  while (current) {
    append_node(current->value * multiplier, &new_list);
    advance_list(&current);
  }

  return new_list;
}

void print_list(node *list) {
  node *current = list;
  rewind_list(&current);

  while (current) {
    printf("%d ", current->value);
    advance_list(&current);
  }

  printf("\n");
}

node *merge_lists(node *list_1, node *list_2) {
  node *l1_cur = list_1;
  node *l2_cur = list_2;
  node *new_list = NULL;

  rewind_list(&l1_cur);
  rewind_list(&l2_cur);

  while (l1_cur && l2_cur) {
    if (l1_cur->value == l2_cur->value) {
      append_node(l1_cur->value, &new_list);
      advance_list(&l1_cur);
      advance_list(&l2_cur);
    } else if (l1_cur->value < l2_cur->value) {
      append_node(l1_cur->value, &new_list);
      advance_list(&l1_cur);
    } else {
      append_node(l2_cur->value, &new_list);
      advance_list(&l2_cur);
    }
  }

  while (l1_cur) {
    append_node(l1_cur->value, &new_list);
    advance_list(&l1_cur);
  }

  while (l2_cur) {
    append_node(l2_cur->value, &new_list);
    advance_list(&l2_cur);
  }

  return new_list;
}

void rewind_list(node **list) {
  if (!*list) return;
  while ((*list)->prev) {
    *list = (*list)->prev;
  }
}

void fast_forward_list(node **list) {
  if (!*list) return;
  while ((*list)->next) {
    *list = (*list)->next;
  }
}

void advance_list(node **list) {
  if (!*list) return;
  *list = (*list)->next;
}
