#include <stdio.h>

int main(){
    static int arr[10];
    for (int i = 0; i < 10; i++){
        arr[i] = i;
    }
    for (int i = 0; i < 10; i++){
        printf("%d\n", arr + i);
        printf("arr: %d\n", arr[i]);
    }

    for(int i = 0; i < 10; i++){
        printf("%d\n", *(arr + i));
        printf("%d\n", &arr[i]);
    }
}

