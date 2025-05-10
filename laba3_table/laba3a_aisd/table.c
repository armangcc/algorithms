#include "table.h"

typedef struct KeySpace{
    char* data;
    size_t key;
}KeySpace;


struct Table {
    KeySpace* ks;
    size_t maxsize;
    size_t csize;
};


//initializing table
Table* create_table(size_t maxsize){
    if (maxsize == 0){
        fprintf(stderr, "Size must be more than 0\n");
        return NULL;
    }

    Table* table = malloc(sizeof(Table));
    if (table == NULL){
        fprintf(stderr, "Memory for table not allocated\n");
        return NULL;
    }

    table->ks = malloc(maxsize * sizeof(KeySpace)); //create array of keys in table
    if (table->ks == NULL){
        fprintf(stderr, "Memory for keyspace not allocated\n");
        free(table);
        return NULL;
    }

    table->maxsize = maxsize;
    table->csize = 0; // because current size is 0, after adding alements current size will increase
    fprintf(stdout, "Table was created successfuly\n");
    return table;
}


int insert(Table* table, size_t new_key, char* info){
    if (table == NULL){
        fprintf(stderr, "Memory for table not allocated\n");
        return 1;
    }

    if (info == NULL){
        //напишешь строка = NULL;
        return 1;
    }

    if (table->csize >= table->maxsize){
        fprintf(stderr, "Table is full");
        return 1;
    }

    //check uniqe of key
    for(int i = 0; i < table->csize; i++){
        if (new_key == table->ks[i].key){
            fprintf(stderr, "Such key %d already exists\n", new_key);
            return 1;
        }
    }

    table->ks[table->csize].key = new_key;
    table->ks[table->csize].data = strdup(info);
    table->csize++;
    return 0; //success
}


int delete(Table* table, size_t key){ //key which must be deleted
    if (table == NULL){
        fprintf(stderr, "Memory for table not allocated\n");
        return 1;
    }

    for (int i = 0; i < table->csize; i++){
        if (key == table->ks[i].key){
            free(table->ks[i].data);
            for (int j = i; j < table->csize - 1; j++){
                table->ks[j] = table->ks[j + 1];
            }
            table->csize--;
            return 0; //success
        }
    }

    return 1;//error: key was not found
}


char* search(Table* table, size_t key){
    if (table == NULL){
        fprintf(stderr, "Memory for table not allocated\n");
        return NULL;
    }

    for (int i = 0; i < table->csize; i++){
        if (key == table->ks[i].key){
            return table->ks[i].data;
        }
    }

    return NULL; //error: there is not such key
}


int free_table(Table* table){
    if (table == NULL){
        return 1; //table was not allocated
    }

    //free strings in all keyspace
    for(int i = 0; i < table->csize; i++){
        free(table->ks[i].data);
    }

    free(table->ks);
    free(table);
    table->csize = 0;
    return 0; //success
}


void print_table(Table* table){
    if (table == NULL){
        fprintf(stderr, "Table was not allocated");
        return;
    }

    if (table->csize == 0 || table->maxsize == 0){
        fprintf(stderr, "Table is empty");
        return;
    }

    for(int i = 0; i < table->csize; i++){
        fprintf(stdout, "Key: %d/t Value: %s \n", table->ks[i].key, table->ks[i].data);
        return;
    }
}


Table* search_range(const Table* table, size_t start, size_t end) {
    // Проверка входных данных
    if (!table || start > end) {
        fprintf(stderr, "Ошибка: неверные аргументы\n");
        return NULL;
    }

    // Создаём таблицу для результатов (максимальный размер = table->csize)
    Table* result = create_table(table->csize);
    if (!result) {
        perror("Ошибка создания таблицы");
        return NULL;
    }

    // Поиск элементов в диапазоне
    for (size_t i = 0; i < table->csize; i++) {
       size_t current_key = table->ks[i].key;
        if (current_key >= start && current_key <= end) {
            // Копируем строку (аналог strdup)
            char* info_copy = malloc(strlen(table->ks[i].data) + 1);
            if (!info_copy) {
                perror("Ошибка копирования строки");
                free_table(result); // Важно: освобождаем память перед выходом
                return NULL;
            }
            strcpy(info_copy, table->ks[i].data);

            // Добавляем элемент в результат
            result->ks[result->csize].key = current_key;
            result->ks[result->csize].data = info_copy;
            result->csize++;
        }
    }

    // Если ничего не найдено
    if (result->csize == 0) {
        free_table(result);
        return NULL;
    }

    return result;
}




