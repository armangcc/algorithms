#ifndef ARRAY_H
#define ARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#define SUCCESS 0
#define NOT_ENOUGH_MEMORY 1
#define NULL_POINTER_ERROR 2
#define INDEX_IS_OUT_OF_RANGE 10
#define WRONG_LIMITS_ERROR 11
#define ARRAY_MAX_SIZE 1000 * 1000 * 1000


int read_int(int *value, const int lower_limit, const int upper_limit);
int initialize_array(int **array, int *size);
int insert_element(int **array, int *size, int index, int value);
int delete_element(int **array, int *size, int index);
int find_unique_elements(int **array, int *size);
int print_array(int *array, int size);

#endif