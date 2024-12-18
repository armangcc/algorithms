#include "array.h"


int initialize_array(int **array, int *size, const int capacity) {
    /*capacity: Memmory measured in ints*/
    if  (NULL == array || NULL == size) {
        return NULL_POINTER_ERROR;
    }
    printf("Enter the length of the array ");
    int error = read_int(size, 1, ARRAY_MAX_SIZE);
    if (error == EOF) {
        printf("You completed the program");
        return EOF;
    }
    if (capacity < *size) {
        return NOT_ENOUGH_MEMORY;
    }
    *array = (int *) malloc(sizeof(int) * capacity);
    if (NULL == *array) {
        return NOT_ENOUGH_MEMORY;
    }
    for (int i = 0; i < *size; i++) {
        printf("Enter element %d: ", i + 1);
        error = read_int((*array) + i, INT_MIN, INT_MAX);
        if (SUCCESS != error) {
            free(*array);
            *array = NULL;
            return error;
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
    for (int i = index; i < *size - 1; i++) {
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


int find_unique_elements(const int *array, int size, int **unique_array, int *unique_size) {
    if (array == NULL || size <= 0 || unique_array == NULL || unique_size == NULL) {
        return NULL_POINTER_ERROR;
    }
    *unique_array = malloc(size * sizeof(int));
    if (*unique_array == NULL) {
        return NOT_ENOUGH_MEMORY;
    }
    int temp_size = 0;
    for (int i = 0; i < size; i++) {
        int count = 0;
        for (int j = 0; j < size; j++) {
            if (array[i] == array[j]) {
                count++;
            }
        }
        if (count == 1) {
            (*unique_array)[temp_size++] = array[i];
        }
    }
    *unique_size = temp_size;
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


int read_int(int *value, const int lower_limit, const int upper_limit) {
    if (value == NULL) {
        return NULL_POINTER_ERROR;
    }
    if (lower_limit > upper_limit) {
        return WRONG_LIMITS_ERROR;
    }
    char buffer[100];
    while (true) {
        printf("Enter a number: ");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            return EOF;
        }
        // Проверяем, состоит ли строка только из числа
        char *endptr;
        long temp_value = strtol(buffer, &endptr, 10);
        if (*endptr != '\n' && *endptr != '\0') {
            printf("Invalid input. Only numbers are allowed! Try again.\n");
            continue;
        }
        if (temp_value < lower_limit || temp_value > upper_limit) {
            printf("Value is out of range! Enter value in range [%d ; %d]: ", lower_limit, upper_limit);
            continue;
        }
        *value = (int) temp_value;
        return SUCCESS; // Корректный ввод
    }
}