#include "array.h"


int initialize_array(int **array, int *size) {
    if  (NULL == array || NULL == size) {
        return NULL_POINTER_ERROR;
    }
    printf("Enter the length of the array: ");
    if (read_int(size, 1, ARRAY_MAX_SIZE) != SUCCESS) {
        return WRONG_LIMITS_ERROR;
    }
    *array = calloc(*size, sizeof(int));
    if (NULL == *array) {
        return NOT_ENOUGH_MEMORY;
    }
    for (int i = 0; i < *size; i++) {
        printf("Enter element %d: ", i + 1);
        if (scanf("%d", &(*array)[i]) != 1) {
            return EOF;
        }
    }
    return SUCCESS;
}


int insert_element(int **array, int *size, int index, int value) {
    if (NULL == array || NULL == size) {
        return NULL_POINTER_ERROR;
    }
    if (index > *size) {
        index = *size;
    }

    int *temp = realloc(*array, (*size + 1) * sizeof(int));
    if (temp == NULL) {
        return NOT_ENOUGH_MEMORY;
    }
    *array = temp;
    if (*array == NULL) { //Эта строка нужна? ведь проверка осуществляется на 35 строке и array не может быть NULL
        return 1;
    }
    for (int i = *size; i > index; i--) {
        (*array)[i] = (*array)[i - 1];
    }
    (*array)[index] = value;
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
    if (1 == *size){
        *size = 0;
        free(*array);
        *array = NULL;
        return SUCCESS;
    }
    for (int i = index - 1; i < *size - 1; i++) {
        (*array)[i] = (*array)[i + 1];
    }
    int *temp = realloc(*array, (*size - 1) * sizeof(int));
    if (temp == NULL) {
        return NOT_ENOUGH_MEMORY;
    }
    *array = temp;
    (*size)--;
    return SUCCESS;
}


int find_unique_elements(int **array, int *size) {
    if (array == NULL || size == 0) return NULL_POINTER_ERROR;
    int *temp = malloc(*size * sizeof(int));
    if (NULL == temp) return NOT_ENOUGH_MEMORY;
    int temp_size = 0;
    for (int i = 0; i < *size; i++) {
        int count = 0;
        for (int j = 0; j < *size; j++) {
            if ((*array)[i] == (*array)[j]) count++;
        }
        if (count == 1) {
            temp[temp_size++] = (*array)[i];
        }
    }
    free(*array);
    *array = malloc(temp_size * sizeof(int));
    if (*array == NULL) {
        free(temp);
        return NOT_ENOUGH_MEMORY;
    }

    for (int i = 0; i < temp_size; i++) {
        (*array)[i] = temp[i];
    }
    *size = temp_size;
    free(temp);
    return SUCCESS;
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
int read_int(int *value, const int lower_limit, const int upper_limit){
    if (NULL == value){
        return NULL_POINTER_ERROR;
    }
    if (lower_limit > upper_limit){
        return WRONG_LIMITS_ERROR;
    }
    while (true){
        int scanf_returns = scanf("%d", value);
        if (scanf_returns == EOF){
            printf("\nInterrupted by user\n");
            return EOF;
        }
        while (getchar() != '\n');
        if (scanf_returns == 0){
            printf("Only numbers are allowed!\n");
        }
        if (scanf_returns == 1
            && (*value < lower_limit || *value > upper_limit)){
            printf("Value is out of range!\n");
            printf("Enter value in range [%d - %d]\n", lower_limit, upper_limit);
        }
        else if (scanf_returns == 1){
            return SUCCESS;
        }
        printf("Try again: ");
    }
}
