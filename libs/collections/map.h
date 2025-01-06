#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char *key;
    void *value;
} MapEntry;

typedef struct {
    MapEntry *entries;
    size_t size;
    size_t capacity;
} Map;

void map_init(Map *map, size_t initial_capacity);
void map_set(Map *map, const char *key, const void *value, size_t value_size);
void *map_get(Map *map, const char *key);
bool map_remove(Map *map, const char *key);
void map_resize(Map *map, size_t new_capacity);
void map_free(Map *map);

//----------------------------------------------//

void map_init(Map *map, size_t initial_capacity) {
    if (initial_capacity == 0) initial_capacity = 16;
    map->entries = calloc(initial_capacity, sizeof(MapEntry));
    if (!map->entries) {
        fprintf(stderr, "Failed to allocate memory for map\n");
        exit(EXIT_FAILURE);
    }
    map->size = 0;
    map->capacity = initial_capacity;
}

void map_resize(Map *map, size_t new_capacity) {
    if (new_capacity < map->size) {
        fprintf(stderr, "New capacity cannot be smaller than the current size\n");
        return;
    }

    MapEntry *new_entries = calloc(new_capacity, sizeof(MapEntry));
    if (!new_entries) {
        fprintf(stderr, "Failed to allocate memory for map resizing\n");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < map->size; i++) {
        new_entries[i] = map->entries[i];
    }

    free(map->entries);
    map->entries = new_entries;
    map->capacity = new_capacity;
}

void map_set(Map *map, const char *key, const void *value, size_t value_size) {
    for (size_t i = 0; i < map->size; i++) {
        if (strcmp(map->entries[i].key, key) == 0) {
            free(map->entries[i].value);
            map->entries[i].value = malloc(value_size);
            memcpy(map->entries[i].value, value, value_size);
            return;
        }
    }

    if (map->size >= map->capacity) {
        map_resize(map, map->capacity * 2);
    }

    map->entries[map->size].key = strdup(key);
    map->entries[map->size].value = malloc(value_size);
    memcpy(map->entries[map->size].value, value, value_size);
    map->size++;
}

void *map_get(Map *map, const char *key) {
    for (size_t i = 0; i < map->size; i++) {
        if (strcmp(map->entries[i].key, key) == 0) {
            return map->entries[i].value;
        }
    }
    return NULL;
}

bool map_remove(Map *map, const char *key) {
    for (size_t i = 0; i < map->size; i++) {
        if (strcmp(map->entries[i].key, key) == 0) {
            free(map->entries[i].key);
            free(map->entries[i].value);

            for (size_t j = i; j < map->size - 1; j++) {
                map->entries[j] = map->entries[j + 1];
            }
            map->size--;
            return true;
        }
    }
    return false;
}

void map_free(Map *map) {
    for (size_t i = 0; i < map->size; i++) {
        free(map->entries[i].key);
        free(map->entries[i].value);
    }
    free(map->entries);
    map->entries = NULL;
    map->size = 0;
    map->capacity = 0;
}

#endif
