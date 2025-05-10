#ifndef TABLE_H
#define TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Table Table;

Table* create_table(size_t maxsize);
int insert(Table* table, size_t new_key, char* info);
int delete(Table* table, size_t key);
char* search(Table* table, size_t key);
int free_table(Table* table);
void print_table(Table* table);
Table* search_range(const Table* table, size_t start, size_t end);


#endif // TABLE_H
