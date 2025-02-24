#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int num_elements = 10;
    void *initial_brk = sbrk(0);
    printf("Initial program break: %p\n", initial_brk);
    int *arr = (int *)malloc(num_elements * sizeof(int));

    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        return 1;
    }
    for (int i = 0; i < num_elements; ++i) {
        arr[i] = i * i;
    }
    printf("Allocated and initialized memory:\n");
    for (int i = 0; i < num_elements; ++i) {
        printf("arr[%d] = %d\n", i, arr[i]);
    }
    void *new_brk = sbrk(num_elements * sizeof(int));
    if (new_brk == (void *)-1) {
        fprintf(stderr, "Failed to increase data segment size with brk()\n");
    } else {
        printf("Increased program break with brk(): %p\n", new_brk);
    }
    free(arr);
    printf("Memory freed using free().\n");
    new_brk = sbrk(-num_elements * sizeof(int));
    if (new_brk == (void *)-1) {
        fprintf(stderr, "Failed to decrease data segment size with brk()\n");
    } else {
        printf("Decreased program break with brk(): %p\n", new_brk);
    }
    void *final_brk = sbrk(0);
    printf("Final program break: %p\n", final_brk);

    return 0;
}

