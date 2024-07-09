#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"          

#define SIZE 7

typedef struct {
    char* key;
    char* value;
} HashItem;

typedef struct {
    HashItem** items;
} HashTable;

HashTable* create_table() {
    HashTable* table = malloc(sizeof(HashTable));
    table->items = malloc(sizeof(HashItem*) * SIZE);
    for (int i = 0; i < SIZE; i++) {
        table->items[i] = NULL;
    }
    return table;
}

int hash_function(char* key) {
    int sum = 0;
    for (int i = 0; i < strlen(key); i++) {
        sum += key[i];
    }
    return sum % SIZE;
}

void insert(HashTable* table, char* key, char* value) {
    int index = hash_function(key);
    while (table->items[index] != NULL && strcmp(table->items[index]->key, key) != 0) {
        index = (index + 1) % SIZE;
    }
    if (table->items[index] != NULL) {
        free(table->items[index]->value);
    } else {
        table->items[index] = malloc(sizeof(HashItem));
        table->items[index]->key = malloc(strlen(key) + 1);
        strcpy(table->items[index]->key, key);
    }
    table->items[index]->value = malloc(strlen(value) + 1);
    strcpy(table->items[index]->value, value);
}

char* search(HashTable* table, char* key) {
    int index = hash_function(key);
    while (table->items[index] != NULL) {
        if (strcmp(table->items[index]->key, key) == 0) {
            return table->items[index]->value;
        }
        index = (index + 1) % SIZE;
    }
    return NULL;
}

void display(HashTable* table) {
    for (int i = 0; i < SIZE; i++) {
        if (table->items[i]) {
            printf("%s: %s\n", table->items[i]->key, table->items[i]->value);
        }
    }
}