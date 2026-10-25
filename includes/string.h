#pragma once
#include <stdatomic.h>
#include <stddef.h>

typedef struct string_s string_t ;

struct string_s {
    char *value;
    size_t len;
    void (*free)(string_t *);
    void (*resize)(string_t *, size_t);
    void (*copy)(string_t *, char *);
    void (*rewrite)(string_t *, char *);
    void (*rewrite_alloc)(string_t *, char *);
    int (*compare)(string_t *, char *);
    char *(*slicing)(string_t *, size_t, size_t);
    int (*starts_with)(string_t *, char *);
    int (*ends_with)(string_t *, char *);
    void (*cat)(string_t *, char *);
    void (*lstrip)(string_t *);
    void (*rstrip)(string_t *);
    void (*strip)(string_t *);
    size_t (*find)(string_t *, char *);
    size_t (*find_last)(string_t *, char *);
};

struct   string_s newstring(char *val);
void     freestring(string_t *str);
void     string_resize(string_t *str, size_t len);
void     string_copy(string_t *str, char *s);
void     string_rewrite(string_t *str, char *val);
void     string_rewrite_alloc(string_t *str, char *val);
int      string_compare(string_t *str, char *s);
char*    string_slicing(string_t *str, size_t start, size_t end);
int      string_starts_with(string_t *str, char *s);
int      string_ends_with(string_t *str, char *s);
void     string_cat(string_t *str, char *s);
void     string_lstrip(string_t *str);
void     string_rstrip(string_t *str);
void     string_strip(string_t *str);
size_t   string_find(string_t *str, char *s);
size_t   string_find_last(string_t *str, char *s);
