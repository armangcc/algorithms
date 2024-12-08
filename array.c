#include "array.h"


int initialize_array(int **array, int *size) {
    if (NULL == array || NULL == size) {
        return NULL_POINTER_ERROR;
    }

    printf("Enter the length of array: ");
    int scanf_returns = scanf("%d", size);
    if (scanf_returns == EOF) {
        return END_OF_FILE;
    }
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
        int scanf_returns = scanf("%d", &(*array)[i]);
        if (scanf_returns == EOF) {
            return END_OF_FILE;
        }
    }
    return SUCCESS;
}


int insert_element(int **array, int *size, int index, int value) {
    if (NULL == array || NULL == size) {
        return NULL_POINTER_ERROR;
    }
    if (index > *size) {
        index = *size; // Вставка в конец массива
    }

    int *temp = (int *)realloc(*array, (*size + 1) * sizeof(int));
    if (temp == NULL) {
        return NOT_ENOUGH_MEMORY;
    }
    *array = temp;

    if (*array == NULL) {
        return 1;
    }
    for (int i = *size; i > index; i--) {
        (*array)[i] = (*array)[i - 1];
    }
    (*array)[index] = value; //?????
    (*size)++;
    return SUCCESS;
}


int delete_element(int **array, int *size, int index) {
    if (NULL == array || NULL == size) {
        return NULL_POINTER_ERROR;
    }
    if (index < 0 || index >= *size) {
        return  INDEX_IS_OUT_OF_RANGE;
    }
    for (int i = index; i < *size - 1; i++) {
        (*array)[i] = (*array)[i + 1];
    }


    int *temp = (int *)realloc(*array, (*size - 1) * sizeof(int));
    if (temp == NULL) {
        return NOT_ENOUGH_MEMORY;
    }
    *array = temp;

    if (*array == NULL) {
        return NOT_ENOUGH_MEMORY;
    }
    (*size)--;
    return SUCCESS;
}


int find_unique_elements(int **array, int *size) {
    if (NULL == array || NULL == size) {
        return NULL_POINTER_ERROR;
    }
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
    if (NULL == array) {
        return NULL_POINTER_ERROR;
    }
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
