#ifndef FLAGS_H
#define FLAGS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    const char *name;
    const char *alias;
    const char *description;
    const char *default_value;
    const char *value;
    bool is_set;
} Flag;

typedef struct {
    Flag *flags;
    size_t count;
    size_t capacity;
} FlagManager;

FlagManager *create_flag_manager(size_t capacity) {
    FlagManager *manager = (FlagManager *)malloc(sizeof(FlagManager));
    manager->flags = (Flag *)malloc(capacity * sizeof(Flag));
    manager->count = 0;
    manager->capacity = capacity;
    return manager;
}

void add_flag(FlagManager *manager, const char *name, const char *alias, const char *description, const char *default_value) {
    if (manager->count >= manager->capacity) {
        manager->capacity *= 2;
        manager->flags = (Flag *)realloc(manager->flags, manager->capacity * sizeof(Flag));
    }
    Flag flag = {name, alias, description, default_value, default_value, false};
    manager->flags[manager->count++] = flag;
}

void parse_flags(FlagManager *manager, int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        for (size_t j = 0; j < manager->count; j++) {
            Flag *flag = &manager->flags[j];
            if ((strcmp(argv[i], flag->name) == 0 || (flag->alias && strcmp(argv[i], flag->alias) == 0)) && i + 1 < argc) {
                flag->value = argv[++i];
                flag->is_set = true;
            }
        }
    }
}

const char *get_flag_value(FlagManager *manager, const char *name) {
    for (size_t i = 0; i < manager->count; i++) {
        if (strcmp(manager->flags[i].name, name) == 0) {
            return manager->flags[i].value;
        }
    }
    return NULL;
}

void print_help(FlagManager *manager) {
    printf("Usage:\n");
    for (size_t i = 0; i < manager->count; i++) {
        Flag *flag = &manager->flags[i];
        printf("  %s, %s\t%s (default: %s)\n",
               flag->name,
               flag->alias ? flag->alias : "",
               flag->description,
               flag->default_value);
    }
}

void free_flag_manager(FlagManager *manager) {
    free(manager->flags);
    free(manager);
}

// Example Usage
// int main(int argc, char **argv) {
//     FlagManager *flags = create_flag_manager(10);
//
//     add_flag(flags, "--help", "-h", "Show this help message", NULL);
//     add_flag(flags, "--name", "-n", "Your name", "World");
//     add_flag(flags, "--age", "-a", "Your age", "0");
//
//     parse_flags(flags, argc, argv);
//
//     if (get_flag_value(flags, "--help")) {
//         print_help(flags);
//         free_flag_manager(flags);
//         return 0;
//     }
//
//     const char *name = get_flag_value(flags, "--name");
//     const char *age = get_flag_value(flags, "--age");
//
//     printf("Hello, %s! You are %s years old.\n", name, age);
//
//     free_flag_manager(flags);
//     return 0;
// }

#endif