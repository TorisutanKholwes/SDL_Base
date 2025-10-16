/*
 * Copyright (c) 2025 Torisutan
 * ALl rights reserved
 */
#include "list.h"
#include "logger.h"
#include "utils.h"
#include "string_builder.h"

List* List_create() {
    List* list = calloc(1, sizeof(List));
    if (!list) {
        error("Failed to allocate memory for List");
        return NULL;
    }
    list->head = calloc(1, sizeof(ListNode));
    if (!list->head) {
        error("Failed to allocate memory for ListNode");
        safe_free((void**)&list);
        return NULL;
    }
    list->head->prev = list->head;
    list->head->next = list->head;
    list->size = 0;
    return list;
}

void List_destroy(List* list) {
    if (!list) return;
    List_clear(list);
    safe_free((void**)&list);
}

void List_clear(List* list) {
    ListNode* node = list->head;
    while (node) {
        ListNode* next = node->next;
        safe_free((void**)&next);
        node = next;
    }
    list->size = 0;
    list->head->prev = list->head;
    list->head->next = list->head;
}

void List_push(List* list, void* value) {
    ListNode* node = calloc(1, sizeof(ListNode));
    if (!node) {
        error("Failed to allocate memory for ListNode");
        return;
    }
    ListNode* last = list->head->prev;
    list->head->prev = node;
    node->value = value;
    node->prev = last;
    node->next = list->head;
    last->next = node;
    list->size++;
}

void List_remove(List* list, void* value) {
    ListNode* node = list->head->next;
    while (node != list->head) {
        if (node->value == value) {
            ListNode* prev = node->prev;
            ListNode* next = node->next;
            prev->next = next;
            next->prev = prev;
            safe_free((void**)&node);
            list->size--;
            return;
        }
        node = node->next;
    }
}

void* List_pop(List* list, size_t index) {
    if (index >= list->size || list->size == 0) {
        error("Index out of bounds");
        return NULL;
    }
    ListNode* node = list->head->next;
    for (size_t i = 0; i < index; i++) {
        node = node->next;
    }
    void* value = node->value;
    ListNode* prev = node->prev;
    ListNode* next = node->next;
    prev->next = next;
    next->prev = prev;
    safe_free((void**)&node);
    list->size--;
    return value;
}

size_t List_size(List* list) {
    return list->size;
}

bool List_empty(List* list) {
    return list->size == 0;
}

bool List_contains(List* list, void* value) {
    ListNode* node = list->head->next;
    while (node != list->head) {
        if (node->value == value) {
            return true;
        }
        node = node->next;
    }
    return false;
}

void* List_get(List* list, size_t index) {
    if (index >= list->size) {
        error("Index out of bounds");
        return NULL;
    }
    ListNode* node = list->head->next;
    for (size_t i = 0; i < index; i++) {
        node = node->next;
    }
    return node->value;
}

void List_set(List* list, size_t index, void* value) {
    if (index >= list->size) {
        error("Index out of bounds");
        return;
    }
    ListNode* node = list->head->next;
    for (size_t i = 0; i < index; i++) {
        node = node->next;
    }
    node->value = value;
}

char* List_toString(List* list, const char* format, void* (*formatValueFunc)(void* value)) {
    StringBuilder* sb = StringBuilder_create(DEFAULT_CAPACITY);
    if (!sb) return NULL;
    StringBuilder_append(sb, "[");
    ListNode* node = list->head->next;
    while (node != list->head) {
        void* value = node->value;
        if (formatValueFunc) {
            value = formatValueFunc(node->value);
        }
        if (strstr(format, "f")) {
            StringBuilder_append_format(sb, format, *(float*)value);
        } else if (strstr(format, "lf")) {
            StringBuilder_append_format(sb, format, *(double*)value);
        }  else {
            StringBuilder_append_format(sb, format, value);
        }
        if (node->next != list->head) {
            StringBuilder_append(sb, ", ");
        }
        node = node->next;
    }
    StringBuilder_append(sb, "]");
    char* result = StringBuilder_build(sb);
    StringBuilder_destroy(sb);
    return result;
}