#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char *key;
    void *value;
} HashMapEntry;

typedef struct {
    HashMapEntry *entries;
    size_t size;
    size_t capacity;
} HashMap;

void hashmap_init(HashMap *map, size_t initial_capacity);
void hashmap_set(HashMap *map, const char *key, const void *value, size_t value_size);
void *hashmap_get(HashMap *map, const char *key);
bool hashmap_remove(HashMap *map, const char *key);
void hashmap_resize(HashMap *map, size_t new_capacity);
void hashmap_free(HashMap *map);
static size_t hashmap_hash(const char *key, size_t capacity);

//----------------------------------------------//
//----------------------------------------------//

static size_t hashmap_hash(const char *key, size_t capacity) {
    size_t hash = 0;
    for (const char *ptr = key; *ptr != '\0'; ++ptr) {
        hash = (hash * 31 + *ptr) % capacity;
    }
    return hash;
}

void hashmap_init(HashMap *map, size_t initial_capacity) {
    if (initial_capacity == 0) initial_capacity = 16;
    map->entries = calloc(initial_capacity, sizeof(HashMapEntry));
    if (!map->entries) {
        fprintf(stderr, "Failed to allocate memory for hashmap\n");
        exit(EXIT_FAILURE);
    }
    map->size = 0;
    map->capacity = initial_capacity;
}

void hashmap_resize(HashMap *map, size_t new_capacity) {
    HashMapEntry *old_entries = map->entries;
    size_t old_capacity = map->capacity;

    map->entries = calloc(new_capacity, sizeof(HashMapEntry));
    if (!map->entries) {
        fprintf(stderr, "Failed to allocate memory for hashmap resizing\n");
        exit(EXIT_FAILURE);
    }
    map->size = 0;
    map->capacity = new_capacity;

    for (size_t i = 0; i < old_capacity; i++) {
        HashMapEntry *entry = &old_entries[i];
        if (entry->key != NULL) {
            hashmap_set(map, entry->key, entry->value, sizeof(void *));
            free(entry->key);
            free(entry->value);
        }
    }
    free(old_entries);
}

void hashmap_set(HashMap *map, const char *key, const void *value, size_t value_size) {
    if (map->size >= map->capacity / 2) {
        hashmap_resize(map, map->capacity * 2);
    }

    size_t index = hashmap_hash(key, map->capacity);
    while (map->entries[index].key != NULL) {
        if (strcmp(map->entries[index].key, key) == 0) {
            free(map->entries[index].value);
            map->entries[index].value = malloc(value_size);
            memcpy(map->entries[index].value, value, value_size);
            return;
        }
        index = (index + 1) % map->capacity;
    }

    map->entries[index].key = strdup(key);
    map->entries[index].value = malloc(value_size);
    memcpy(map->entries[index].value, value, value_size);
    map->size++;
}

void *hashmap_get(HashMap *map, const char *key) {
    size_t index = hashmap_hash(key, map->capacity);
    while (map->entries[index].key != NULL) {
        if (strcmp(map->entries[index].key, key) == 0) {
            return map->entries[index].value;
        }
        index = (index + 1) % map->capacity;
    }
    return NULL;
}

bool hashmap_remove(HashMap *map, const char *key) {
    size_t index = hashmap_hash(key, map->capacity);
    while (map->entries[index].key != NULL) {
        if (strcmp(map->entries[index].key, key) == 0) {
            free(map->entries[index].key);
            free(map->entries[index].value);
            map->entries[index].key = NULL;
            map->entries[index].value = NULL;
            map->size--;

            size_t next_index = (index + 1) % map->capacity;
            while (map->entries[next_index].key != NULL) {
                HashMapEntry entry = map->entries[next_index];
                map->entries[next_index].key = NULL;
                map->entries[next_index].value = NULL;
                map->size--;
                hashmap_set(map, entry.key, entry.value, sizeof(void *));
                free(entry.key);
                free(entry.value);
                next_index = (next_index + 1) % map->capacity;
            }
            return true;
        }
        index = (index + 1) % map->capacity;
    }
    return false;
}

void hashmap_free(HashMap *map) {
    for (size_t i = 0; i < map->capacity; i++) {
        if (map->entries[i].key != NULL) {
            free(map->entries[i].key);
            free(map->entries[i].value);
        }
    }
    free(map->entries);
    map->entries = NULL;
    map->size = 0;
    map->capacity = 0;
}

#endif