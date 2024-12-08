



#ifndef ARRAY_H
#define ARRAY_H

#include <stdio.h>
#include <stdlib.h>


#define SUCCESS 0
#define NOT_ENOUGH_MEMORY 1
#define NULL_POINTER_ERROR 2
#define INDEX_IS_OUT_OF_RANGE 10
#define END_OF_FILE 20

int initialize_array(int **array, int *size);
int insert_element(int **array, int *size, int index, int value);
int delete_element(int **array, int *size, int index);
int find_unique_elements(int **array, int *size);
int print_array(int *array, int size);

#endif
