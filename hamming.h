typedef struct list_node {
  int value;
  struct list_node *next;
  struct list_node *prev;
} node;

void append_node(int value, node **list);
void free_list(node *current);
node *initialize_list(int value);
node *generate_terms(node *list, int multiplier);
void print_list(node *list);
node *merge_lists(node *list_1, node *list_2);
void rewind_list(node **list);
void fast_forward_list(node **list);
void advance_list(node **list);
node *node_at_index(node *final_list, int count);
int has_enough_terms(node *final_list, node *temp_list, int terms);
int list_count(node *list);
void print_count_nodes(node *list, int count);
void free_nodes(node *list);
