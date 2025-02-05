#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int length;
    int capacity;
    int *array;
} Array;

/**************************************************************************/
/* FUNCTION SIGNATURES                                                    */
/**************************************************************************/
int main(void);
void init(Array*, int);
void insert(Array*, int);
void insertAt(Array*,int ,int);
void removeAt(Array*, int);
void search(Array*, int);
void update(Array*,int ,int);
void merge(Array*, Array*);
Array* concat(Array*, Array*);
void print(Array*);
void reverse(Array*);
void freeArray(Array*);

/**************************************************************************/
/* FUNCTION DEFINATIONS                                                   */
/**************************************************************************/

void init(Array* a, int capacity){
    if (a->array != NULL){
        fprintf(stderr, "Array is already initialized!\n");
        return;
    }
    if (capacity <= 0) {
        fprintf(stderr, "Capacity must be greater than 0!\n");
        exit(1);
    }
    a->capacity = capacity;
    a->length = 0;
    a->array = (int*) malloc(capacity * sizeof(int));
    if (!a->array) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(1);
    }
    memset(a->array, 0, capacity * sizeof(int));

}


void insert(Array* a, int value) {
    if (a == NULL || a->array == NULL) {
        fprintf(stderr, "Array is not initialized!\n");
        exit(1);
    }

    if (a->length == a->capacity) {
        a->capacity *= 2;
        int* tmp = (int*) realloc(a->array, a->capacity * sizeof(int));
        if (!tmp) {
            fprintf(stderr, "Memory Reallocation Failed!\n");
            freeArray(a);
            exit(1);
        }
        a->array = tmp;
        memset(a->array + a->length, 0, (a->capacity - a->length) * sizeof(int));
    }
    a->array[a->length++] = value;
}


void insertAt(Array* a, int index , int value){
    if(index < 0 || index >= a->capacity){
        fprintf(stderr, "index out of bounds!\n");
        freeArray(a);
        exit(1);
    }

    if(a->length == a->capacity){
        a->capacity *= 2;
        int* tmp = (int*) realloc(a->array, a->capacity * sizeof(int));
        if(tmp == NULL){
            // REALLOC FAILED
            fprintf(stderr, "Memory Reallocation Failed!\n");
            freeArray(a);
            exit(1);
        }
        memset(a->array + a->length, 0, (a->capacity - a->length) * sizeof(int));
        a->array = tmp;
    }

    for(int i = a->length - 1; i >= index; i--){
        a->array[i+1] = a->array[i];
    }
    a->array[index] = value;
    a->length++;
    return;
}

void removeAt(Array* a, int index){
    
    if(index < 0 || index >= a->capacity){
        fprintf(stderr, "index out of bounds!\n");
        free(a);
        exit(1);
    }
    for(int i = index; i < a->length; i++){
        a->array[i] = a->array[i+1];
    }
    a->length--;
}

void update(Array*a, int index, int value){
    if(index < 0 || index >= a->capacity){
        fprintf(stderr, "index out of bounds!\n");
        freeArray(a);
        exit(1);
    }
    a->array[index] = value;
}

void print(Array* a){
    for(int i = 0; i < a->capacity; i++){
        printf("%d ",*(a->array+i));
    }
    printf("\n");
}

void search(Array* a, int target){
    for(int i=0; i<a->length; i++){
        if(*(a->array+i) == target){
            printf("%d is at %d index!\n",target, i);
            return;
        }
    }
    printf("%d not found!\n",target);
};
void merge(Array* a, Array* b){
    if(a->capacity < (a->length + b->length)){
        a->capacity += b->length;
        int* tmp = realloc(a->array, a->capacity * sizeof(int));
        if(tmp == NULL){
            fprintf(stderr, "Memory Reallocation Failed!\n");
            freeArray(a);
            exit(1);
        }

        memset(a->array + a->length, 0, (a->capacity - a->length) * sizeof(int));
        a->array = tmp;
    }
    for(int i=0; i<b->length; i++){
        a->array[a->length+i] = b->array[i];
    }
    a->length += b->length;

};


Array* concat(Array* a, Array* b){
    Array* result = (Array*) malloc(sizeof(Array));
    memset(result, 0 , sizeof(Array));
    init(result, a->length + b->length);
    for(int i = 0; i < a->length; i++){
        insert(result, a->array[i]);
    }
    result->length = a->length;
    for(int i = 0; i < b->length; i++){
        insert(result, b->array[i]);
    }
    result->length += b->length;
    return result;
};


void reverse(Array* a){
    int i = 0;
    int j = a->length - 1;
    while(i < j){
        int tmp = a->array[i];
        a->array[i] = a->array[j];
        a->array[j] = tmp;
        i++;
        j--;
    }
};

void freeArray(Array* a){
    free(a->array);
    free(a);
}
int main(void){
    Array* a = (Array*) malloc(sizeof(Array));
    memset(a, 0, sizeof(Array));
    init(a,3);
    for(int i=1; i<=3; i++){
        insert(a,i);
    }
    print(a);
    init(a,3);
    freeArray(a);
    return 0;
}
