#include <stdio.h>
#include <stdlib.h>

struct s_node { 
    int data;
    struct s_node *next;
};

typedef struct s_node Node;

typedef struct {
    Node* head;
    Node* tail;
    int length;
} LinkedList;

void link(LinkedList* list, int data) {

    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    node->data = data;
    node->next = NULL;

    if (list->head == NULL) {
        list->head = node;
        list->tail = node;
    } else { 
        list->tail->next = node;
        list->tail = node;
    }
    list->length++;
}

void insert(LinkedList* list, int index, int data){
    list->length++;

    if(index == 0){
        Node* node  = (Node*) malloc(sizeof(Node));
        node->next = list->head;
        list->head = node;
        return;
    }

    if(index >= list->length){
        link(list,data);
        return;
    }
    Node* node  = (Node*) malloc(sizeof(Node));
    node = list->head;

    Node* newNode = (Node*) malloc(sizeof(Node));
    while(index-1 > 0){
        node=node->next;
        index--;
    }
    newNode->data = data;
    newNode->next = node->next;
    node->next = newNode;
}

void print(LinkedList* list) {
    Node* node = list->head;
    while (node != NULL) {
        printf("%d", node->data);
        if (node->next != NULL) printf(" -> ");
        node = node->next;
    }
    printf("\n");
}


LinkedList* init(){
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    if (list == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    list->head = NULL;
    list->tail = NULL;
    list->length = 0;
    return list;
}


void freeList(LinkedList* list){
    Node* current = list->head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}

int main() {
    LinkedList* list = init();
    link(list, 1);
    link(list, 2);
    link(list, 3);
    link(list, 4);
    link(list, 5);
    link(list, 6);
    print(list);
    printf("%d\n", list->length);
    insert(list, 6, 7);
    print(list);
    printf("%d\n", list->length);
    insert(list, 0, 0);
    print(list);
    printf("%d\n", list->length);
    freeList(list);
    return 0;
}
