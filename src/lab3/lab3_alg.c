#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct node {
    int data;
    struct node *next; 
} node;

//static node* create_node(int d);
//static node* fill_linked_list();
//static void print_linked_list(node* head);
//static int find_repeat_nodes(node* head, int data);
//static void delete_node(node** head, node* node_to_remove);
//static void delete_linked_list(node** head);

static void delete_node(node** head, node* node_to_remove) {
    if(*head == node_to_remove) {
        *head = node_to_remove->next;
        free(node_to_remove);
        return;
    }

    node *ptr = *head;
    while (ptr != NULL && ptr->next != node_to_remove) {
        ptr = ptr->next;
    }
    if (ptr == NULL) return;

    ptr->next = node_to_remove->next;
    free(node_to_remove);
}

static node* fill_linked_list() {
    node *head = NULL, *tmp = NULL;
    int num;
    char ch;
    
    if (scanf("%d", &num) != 1) {
        delete_linked_list(&head);
        return NULL;
    }
    
    head = create_node(num);
    tmp = head;

    ch = getchar();
    if (ch == '\n' || ch == EOF) return head;

    if (ch != ' ') {
        if (head != NULL) delete_linked_list(&head);
        return NULL;
    } 

    while (1) {
        if (scanf("%d", &num) != 1) {
            delete_linked_list(&head);
            return NULL;
        }

        ch = getchar();

        node *next_tmp = create_node(num);
        tmp->next = next_tmp;
        tmp = next_tmp;
        
        if (ch == '\n' || ch == EOF) break;

        if (ch != ' ') {
            if (head != NULL) delete_linked_list(&head);
            return NULL;

        } 
        
    }

    return head;
}
static void print_linked_list(node* head) {
    node* ptr = head;
    while (ptr != NULL) {
        const char* format_str = ptr->next == NULL ? "%d" : "%d,  ";
        printf(format_str, ptr->data);
        ptr = ptr->next;
    }
    printf("\n");
}
static node* create_node(int d) {
    node *newnode = malloc(sizeof(node));
    newnode->data = d;
    newnode->next = NULL;

    return newnode;
}

static int find_repeat_nodes(node* head, int data) {
    node *ptr = head;
    int count = 0;

    while (ptr != NULL) {
        if (ptr->data == data) {
            count++;
        } 
        if (count > 1) return 1;

        ptr = ptr->next;
    }

    return 0;
}

static void delete_linked_list(node** head) {
    while (*head != NULL) {
        delete_node(head, *head);
    }
}

int lab3() {
    node *head = fill_linked_list();
    if (!head) {
        printf("n/a\n");
        return 1;
    }

    printf("Source array: ");
    print_linked_list(head);
    
    node *tmp = head;
    while (tmp != NULL) {
        node *next_node = tmp->next; 
        if (!find_repeat_nodes(head, tmp->data)) delete_node(&head, tmp);
        tmp = next_node;
    }

    printf("Result array: ");
    print_linked_list(head);

    delete_linked_list(&head);

    return 0;
}