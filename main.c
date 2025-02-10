#include "linkedlist.c"

int main(){
    LinkedList* list = init();
    link(list, 1);
    link(list, 2);
    link(list, 3);
    print(list);
    free(list);
}
