#include "array.h"

int main() {
    int *array = NULL;
    int len = 0;
    int capacity = 0;
    char option;

    while (true) {
        printf("\nMENU:\n");
        printf("(a) Enter the amount of memory for the program. Do it before initialize array it is important!\n");
        printf("(b) Initialize array\n");
        printf("(c) Insert new element\n");
        printf("(d) Delete element\n");
        printf("(e) Find all unique items\n");
        printf("(f) Output array\n");
        printf("(g) Exit\n");
        printf("Choose an option: ");
        if (scanf(" %c", &option) != 1) {
            printf("Invalid input. Exiting.\n");
            break;
        }
        while (getchar() != '\n');

        switch (option) {
            case 'a': {
                printf("Enter the amount of memory for the program (in bytes): ");
                int error = read_int(&capacity, 1, ARRAY_MAX_SIZE);
                if (EOF == error) {
                    printf("You completed the program");
                    return 1;
                }
                capacity = (capacity + sizeof(int)) / sizeof(int);
            }


            case 'b': {
                int error = initialize_array(&array, &len, capacity);
                if (EOF == error) {
                    printf("You completed the program\n");
                    return 1;
                }
                else if (error != SUCCESS) {
                    printf("Wrong input, try again\n");
                    while (error != SUCCESS){
                        error = initialize_array(&array, &len, capacity);
                    }
                }
                else if (error == SUCCESS) {
                    print_array(array, len);
                    break;
                }
                break;
            }

            case 'c': {
                int index, value;
                printf("Enter index to insert: ");
                int error = read_int(&index, 0, len);
                if (EOF == error) {
                    printf("You completed the program");
                    return 1;
                }
                else if (error != SUCCESS) {
                    printf("Try again\n");
                }
                printf("Enter value: ");
                if (len >= capacity) {
                    printf("\nArray is full. Cannot insert new element.\n");
                    break;
                }
                int error2 = read_int(&value, INT_MIN, INT_MAX);
                if (error2 == EOF) {
                    printf("You completed the program");
                    return 1;
                }
                else if (error2 != SUCCESS){
                    printf("Wrong input, try again\n");
                    while (error2 != SUCCESS){
                        error2 = read_int(&value, INT_MIN, INT_MAX);
                    }
                }
                if (insert_element(&array, &len, index, value) != SUCCESS) {
                    printf("Failed to insert element.\n");
                }
                print_array(array, len);
                break;
            }
            case 'd': {
                if (len == 0) {
                    printf("Array is empty. Initialize it first.\n");
                    break;
                }
                int index;
                printf("Enter index to delete: ");
                int error = read_int(&index, 0, len - 1);
                if (error == EOF) {
                    printf("You completed the program");
                    return 1;
                }
                if (delete_element(&array, &len, index) != SUCCESS) {
                    printf("Failed to delete element.\n");
                }
                print_array(array, len);
                break;
            }
            case 'e': {
                if (array == NULL || len == 0) {
                    printf("Array is empty. Initialize it first.\n");
                    break;
                }
                int *unique_array = NULL;
                int unique_len = 0;
                int error = find_unique_elements(array, len, &unique_array, &unique_len);
                if (error != SUCCESS) {
                    printf("Failed to find unique elements.\n");
                    break;
                }
                printf("Original array:\n");
                print_array(array, len);
                printf("Unique elements array:");
                print_array(unique_array, unique_len);
                free(unique_array);
                break;
            }
            case 'f': {
                print_array(array, len);
                break;
            }
            case 'g': {
                free(array);
                return 0;
            }
            default: {
                printf("Invalid option. Try again.\n");
                break;
            }
        }
    }

    free(array);
    return 0;
}