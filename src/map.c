/*
 * Copyright (c) 2025 Torisutan
 * ALl rights reserved
 */

#include "map.h"

#include "logger.h"
#include "utils.h"
#include "string_builder.h"

Map* Map_create() {
    Map* map = calloc(1, sizeof(Map));
    if (!map) {
        error("Failed to allocate memory for Map");
        return NULL;
    }
    map->root = calloc(1, sizeof(MapNode));
    if (!map->root) {
        error("Failed to allocate memory for MapNode");
        safe_free((void**)&map);
        return NULL;
    }
    map->root->prev = map->root;
    map->root->next = map->root;
    map->size = 0;
    return map;
}

void Map_destroy(Map* map) {
    if (!map) return;
    Map_clear(map);
    safe_free((void**)&map);
}

void Map_clear(Map* map) {
    MapNode* node = map->root;
    while (node) {
        MapNode* next = node->next;
        safe_free((void**)&next);
        node = next;
    }
    map->size = 0;
    map->root->prev = map->root;
    map->root->next = map->root;
}

void Map_put(Map* map, void* key, void* value) {
    if (Map_containsKey(map, key)) {
        MapNode* curr = Map_find(map, key);
        curr->value = value;
        return;
    }
    MapNode* node = calloc(1, sizeof(MapNode));
    if (!node) {
        error("Failed to allocate memory for MapNode");
        return;
    }
    MapNode* last = map->root->prev;
    map->root->prev = node;
    node->key = key;
    node->value = value;
    node->prev = last;
    node->next = map->root;
    last->next = node;
    map->size++;
}

void* Map_get(Map* map, void* key) {
    MapNode* node = Map_find(map, key);
    if (node) {
        return node->value;
    }
    return NULL;
}

MapNode* Map_find(Map* map, void* key) {
    MapNode* node = map->root->next;
    while (node != map->root) {
        if (node->key == key) {
            return node;
        }
        node = node->next;
    }
    return NULL;
}

bool Map_containsKey(Map* map, void* key) {
    return Map_find(map, key) != NULL;
}

bool Map_containsValue(Map* map, void* value) {
    MapNode* node = map->root->next;
    while (node != map->root) {
        if (node->value == value) {
            return true;
        }
        node = node->next;
    }
    return false;
}

void Map_remove(Map* map, void* key) {
    MapNode* node = Map_find(map, key);
    if (!node) {
        return;
    }
    MapNode* prev = node->prev;
    MapNode* next = node->next;
    prev->next = next;
    next->prev = prev;
    safe_free((void**)&node);
    map->size--;
}

size_t Map_size(Map* map) {
    return map->size;
}

bool Map_isEmpty(Map* map) {
    return map->size == 0;
}

char* Map_toString(Map* map, const char* keyFormat, const char* valueFormat, void* (*formatKeyFunc)(void* key), void* (*formatValueFunc)(void* value)) {
    StringBuilder* sb = StringBuilder_create(DEFAULT_CAPACITY);
    StringBuilder_append(sb, "{");
    MapNode* node = map->root->next;
    while (node != map->root) {
        void* key = node->key;
        void* value = node->value;
        void* formatKey = formatKeyFunc ? formatKeyFunc(key) : key;
        void* formatValue = formatValueFunc ? formatValueFunc(value) : value;
        StringBuilder_append(sb, "\"");
        StringBuilder_append_format(sb, keyFormat, formatKey);
        StringBuilder_append(sb, "\": ");
        if (strstr(valueFormat, "f")) {
            StringBuilder_append_format(sb, valueFormat, *(float*)formatValue);
        } else if (strstr(valueFormat, "lf")) {
            StringBuilder_append_format(sb, valueFormat, *(double*)formatValue);
        } else {
            StringBuilder_append_format(sb, valueFormat, formatValue);
        }
        node = node->next;
        if (node != map->root) {
            StringBuilder_append(sb, ", ");
        }
    }
    StringBuilder_append(sb, "}");
    char* result = StringBuilder_build(sb);
    StringBuilder_destroy(sb);
    return result;
}

MapIterator* Map_iterator(Map* map) {
    MapIterator* iterator = calloc(1, sizeof(MapIterator));
    if (!iterator) {
        error("Failed to allocate memory for MapIterator");
        return NULL;
    }
    iterator->root = map->root;
    iterator->current = map->root;
    return iterator;
}

void MapIterator_destroy(MapIterator* iterator) {
    if (!iterator) return;
    safe_free((void**)&iterator);
}

bool MapIterator_hasNext(MapIterator* iterator) {
    return iterator->current->next != iterator->root;
}

void MapIterator_next(MapIterator* iterator) {
    if (MapIterator_hasNext(iterator)) {
        iterator->current = iterator->current->next;
    }
}

void* MapIterator_key(MapIterator* iterator) {
    return iterator->current->key;
}

void* MapIterator_value(MapIterator* iterator) {
    return iterator->current->value;
}

