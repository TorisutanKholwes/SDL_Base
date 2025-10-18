/*
 * Copyright (c) 2025 Torisutan
 * ALl rights reserved
 */

#pragma once

// Pointer declarations of all types used across the application
typedef struct App App;

typedef struct Input Input;
typedef struct EventHandler EventHandler;

typedef struct ListNode ListNode;
typedef struct List List;
typedef struct ListIterator ListIterator;

typedef enum LogLevel LogLevel;

typedef struct MapNode MapNode;
typedef struct Map Map;
typedef struct MapIterator MapIterator;

typedef struct StringBuilder StringBuilder;

typedef struct Position Position;
typedef struct Color Color;

typedef struct Button Button;
typedef struct Text Text;

typedef struct ResourceManager ResourceManager;

// Structure who's not used as a pointer elsewhere
typedef struct {
    float width, height;
} Size;

// Types of func
typedef void (*EventHandlerFunc)(Input* input, SDL_Event* evt, void* data);