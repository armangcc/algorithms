#include "array.h"

int main() {
    int *array= NULL;
    int len = 0;
    int error;
    char option;

    while (1) {
        printf("MENU:\n");
        printf("(a) initialize array\n");
        printf("(b) Insert new element\n");
        printf("(c) Delete element\n");
        printf("(d) Find all the unique items\n");
        printf("(e) Output array \n");
        printf("(f) Exit\n");

        option = getchar();
        getchar(); // Для считывания символа новой строки после ввода
        switch (option) {
            case 'a': {
                error = initialize_array(&array, &len);
                if (NOT_ENOUGH_MEMORY == error) {
                    printf("Memory error.\n");
                    return EXIT_FAILURE;
                }
                print_array(array, len);
                break;
            }
            case 'b': {
                int index, value;
                printf("Enter index to insert ");
                scanf("%d", &index);
                printf("Enter value: ");
                scanf("%d", &value);
                error = insert_element(&array, &len, index, value);
                if (NOT_ENOUGH_MEMORY == error) {
                    printf("Memory error.\n");
                    return EXIT_FAILURE;
                }
                print_array(array, len);
                break;
            }
            case 'c': {
                int index;
                printf("Enter index to delete: ");
                scanf("%d", &index);
                error = delete_element(&array, &len, index);
                if (NOT_ENOUGH_MEMORY == error){
                    printf("Memory error.\n");
                    return EXIT_FAILURE;
                }
                while (INDEX_IS_OUT_OF_RANGE == error){
                    printf("Index is out of range! Enter again.\n");
                    error = delete_element(&array, &len, index);
                }
                print_array(array, len);
                break;
            }
            case 'd': {
                error = find_unique_elements(&array, &len);
                if (NOT_ENOUGH_MEMORY == error){
                    printf("Memory error.\n");
                    return  EXIT_FAILURE;
                }
                print_array(array, len);
                break;
            }
            case 'e': {
                print_array(array, len);
                break;
            }
            case 'f': {
                free(array);
                return 0;
            }
            default: {
                printf("WRONG INPUT. Choose new option again.\n");
                break;
            }
        }

    }
}
