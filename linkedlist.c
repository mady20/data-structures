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


void error(char* msg){
    fprintf(stderr, msg);
    exit(1);
}
void link(LinkedList* list, int data) {

    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) error("Memory Allocation Failed!\n");
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
    if(index < 0 || index > list->length) error("Index out of bounds!\n");

    Node* node  = (Node*) malloc(sizeof(Node));

    if (node == NULL) error("Memory Allocation Failed!\n");
    
    node->data = data;
    if(index == 0){
        node->next = list->head;
        list->head = node;
        if(list->tail == NULL){
            list->tail = node;
        }
    }else{
        Node* current = list->head;
        for(int i = 0; i < index - 1; i++){
            current = current->next;
        }
        node->next = current->next;
        current->next = node;
        if(node->next == NULL){
            list->tail = node;
        }
    }
    list->length++;
}
void removeNode(LinkedList* list, int index){
    if(index < 0 || index >= list->length) error("Index out of bounds!\n");

    if(list->head == NULL) error("Empty List!\n");
    
    Node* temp;

    if(index == 0){
        temp = list->head;
        list->head = list->head->next;
        if(list->head == NULL){
            list->tail = NULL;
        }
        free(temp);
    }else{
        Node* current = list->head;
        for(int i = 0; i < index - 1; i++){
            current = current->next;
        }
        temp = current->next;
        current->next = current->next->next;
        if (current->next == NULL) {
            list->tail = current;
        }
        free(temp);
        
    }
    list->length--;
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
    if (list == NULL) error("Memory Allocation Failed!\n");
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
    print(list);
    removeNode(list,4);
    print(list);
    printf("%d\n", list->tail->data);
    freeList(list);
    return 0;
}
