/*Ошибки: 1) Не знаю как реализовывать ручное управление памятью
          2) EOF работает только с choose option*/


#include "array.h"

int main() {
    int *array = NULL;
    int len = 0;
    char option;

    while (true) {
        printf("\nMENU:\n");
        printf("(a) Initialize array\n");
        printf("(b) Insert new element\n");
        printf("(c) Delete element\n");
        printf("(d) Find all unique items\n");
        printf("(e) Output array\n");
        printf("(f) Exit\n");
        printf("Choose an option: ");
        if (scanf(" %c", &option) != 1) {
            printf("Invalid input. Exiting.\n");
            break;
        }
        while (getchar() != '\n'); // Очистка буфера ввода

        switch (option) {
            case 'a': {
                if (initialize_array(&array, &len) != SUCCESS) {
                    printf("Failed to initialize array.\n");
                }
                print_array(array, len);
                break;
            }
            case 'b': {
                int index, value;
                printf("Enter index to insert: ");
                if (read_int(&index, 0, len + 1) != SUCCESS) {
                    break;
                }
                printf("Enter value: ");
                if (read_int(&value, INT_MIN, INT_MAX) != SUCCESS) {
                    break;
                }

                if (insert_element(&array, &len, index, value) != SUCCESS) {
                    printf("Failed to insert element.\n");
                }
                print_array(array, len);
                break;
            }
            case 'c': {
                if (len == 0) {
                    printf("Array is empty. Initialize it first.\n");
                    break;
                }
                int index;
                printf("Enter index to delete: ");
                if (read_int(&index, 0, len - 1) != SUCCESS) {
                    break;
                }

                if (delete_element(&array, &len, index) != SUCCESS) {
                    printf("Failed to delete element.\n");
                }
                print_array(array, len);
                break;
            }
            case 'd': {
                if (find_unique_elements(&array, &len) != SUCCESS) {
                    printf("Failed to process unique elements.\n");
                }
                printf("You will continue to work with this array "); //Здесь нужно вывести старый массив
                print_array(array, len);//новый массив уникальных элементов
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
                printf("Invalid option. Try again.\n");
                break;
            }
        }
    }

    free(array);
    return 0;
}
