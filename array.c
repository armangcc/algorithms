#include "array.h"


int initialize_array(int **array, int *size) {
    printf("Enter the length of array: ");
    scanf("%d", size);
    if (*size <0) {
        printf("Length must be positive.\n");
        *size = 0;
        *array = NULL;
    }
    *array = (int *)calloc(*size, sizeof(int));
    if (*array == NULL) {
        return NOT_ENOUGH_MEMORY;
    }
    for (int i = 0; i < *size; i++) {
        printf("Enter element %d (index): ", i + 1);
        scanf("%d", &(*array)[i]);
    }
    return SUCCESS;
}


int insert_element(int **array, int *size, int index, int value) {
    if (index > *size) {
        index = *size; // Вставка в конец массива
    }
    *array = (int *)realloc(*array, (*size + 1) * sizeof(int));
    if (*array == NULL) {
        return 1;
    }
    for (int i = *size; i > index; i--) {
        (*array)[i] = (*array)[i - 1];
    }
    (*array)[index - 1] = value; //?????
    (*size)++;
    return SUCCESS;
}


int delete_element(int **array, int *size, int index) {
    if (index < 0 || index >= *size) {
        return  INDEX_IS_OUT_OF_RANGE;
    }
    for (int i = index; i < *size - 1; i++) {
        (*array)[i] = (*array)[i + 1];
    }

    *array = (int *)realloc(*array, (*size - 1) * sizeof(int));
    if (*array == NULL) {
        return NOT_ENOUGH_MEMORY;
    }
    (*size)--;
    return SUCCESS;
}


int find_unique_elements(int **array, int *size) {
    int *temp = (int *)malloc(*size * sizeof(int));
    if (temp == NULL) {
        return  NOT_ENOUGH_MEMORY;
    }
    int temp_size = 0;
    for (int i = 0; i < *size; i++) {
        int count = 0;
        for (int j = 0; j < *size; j++) {
            if ((*array)[i] == (*array)[j]) {
                count++;
            }
        }
        if (count == 1) {
            temp[temp_size++] = (*array)[i];
        }
    }

    free(*array);
    *array = (int *)malloc(temp_size * sizeof(int));
    if (*array == NULL) {
        return  NOT_ENOUGH_MEMORY;
    }
    for (int i = 0; i < temp_size; i++) {
        (*array)[i] = temp[i];
    }
    *size = temp_size;
    free(temp);
}

 int print_array(int *array, int size) {
    if (size == 0) {
        printf("Array is empty.\n");
        return 1;
    }
    printf("Array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
     printf("\n");
}
