#include "../includes/string.h"
#include <malloc.h>
#include <stddef.h>
#include <stdio.h>

static size_t countlen(char *str) {
    size_t len = 0;
    while (str[len++]);
    len--;
    return len;
}

string_t newstring(char *val) {
    size_t len = countlen(val);
    string_t ret;
    ret.len = len--;
    ret.value = malloc(len);

    ret.free = &freestring;
    ret.resize = &string_resize;
    ret.rewrite = &string_rewrite;
    ret.rewrite_alloc = &string_rewrite_alloc;
    ret.copy = &string_copy;
    ret.compare = &string_compare;
    ret.slicing = &string_slicing;
    ret.starts_with = &string_starts_with;
    ret.ends_with = &string_ends_with;
    ret.cat = &string_cat;
    ret.lstrip = &string_lstrip;
    ret.rstrip = &string_rstrip;
    ret.strip = &string_strip;
    ret.find = &string_find;
    ret.find_last = &string_find_last;

    size_t idx = 0;
    while (*val) ret.value[idx++] = *val++;
    return ret;
}

void freestring(string_t* str) {
    free(str->value);
}

void string_resize(string_t *str, size_t len){
    str->value = realloc(str->value, len);
}

void string_rewrite_alloc(string_t *str, char *s) {
    size_t lens = countlen(s);
    string_resize(str, lens+1);
    size_t len = 0;
    while (*s) {
        str->value[len] = *s;
        s++;
        len++;
    }
    str->value[len] = '\0';
    str->len = lens;
}

void string_rewrite(string_t *str, char *val) {
    freestring(str);
    str->value = val;
}
void string_copy(string_t *str, char *s){
    size_t len = 0;
    while (*s) {
        str->value[len] = *s;
        s++;
        len++;
    }
    str->len = countlen(str->value);
    str->value[str->len] = '\0';
}

void string_cat(string_t *str, char *s) {
    str->value = realloc(str->value, str->len + countlen(s));
    size_t idx = str->len;
    while (*s) {
        str->value[idx] = *s;
        s++;
        idx++;
    }
    str->len = idx;
}

int string_compare(string_t *str, char *s) {
    int ret = 0;
    size_t idx = 0;
    while (*s) {
        ret += *s - str->value[idx];
        idx++;
        s++;
    }
    return ret;
}

char *string_slicing(string_t *str, size_t start, size_t end) {
    if (start > end) return (char *)-1;
    char *buffer = malloc(end - start);
    size_t idx = 0;
    while (start <= end) {
        buffer[idx] = str->value[start];
        idx++;
        start++;
    }
    return buffer;
}

int string_starts_with(string_t *str, char *s){
    size_t slen = countlen(s);
    char *buffer = string_slicing(str, 0, slen);
    size_t idx = 0;
    while (*s) {
        if (buffer[idx] != *s){
            return 0;
        }
        s++;
        idx++;
    }
    free(buffer);
    return 1;
}

int string_ends_with(string_t *str, char *s){
    size_t slen = countlen(s);
    char *buffer = string_slicing(str, str->len - slen, str->len);
    size_t idx = 0;
    while (*s) {
        if (buffer[idx] != *s){
            return 0;
        }
        s++;
        idx++;
    }
    free(buffer);
    return 1;
}

void string_lstrip(string_t *str){
    size_t idx = 0;
    while ( str->value[idx] == 9  ||
            str->value[idx] == 10 ||
            str->value[idx] == 11 ||
            str->value[idx] == 12 ||
            str->value[idx] == 13 ||
            str->value[idx] == ' '
        ) {
            idx++;
    }
    char *buffer = string_slicing(str, idx, str->len);
    string_rewrite(str, buffer);
    str->len = countlen(buffer);
}

void string_rstrip(string_t *str){
    size_t idx = str->len - 1;
    while ( str->value[idx] == 9  ||
            str->value[idx] == 10 ||
            str->value[idx] == 11 ||
            str->value[idx] == 12 ||
            str->value[idx] == 13 ||
            str->value[idx] == ' '
        ) {
            if (idx == 0) break;
            idx--;
        }
    str->value[idx + 1] = '\0';
    str->len = countlen(str->value);
}

void string_strip(string_t *str){
    string_lstrip(str);
    string_rstrip(str);
}

size_t string_find(string_t *str, char *s){
    size_t idx = 0;
    size_t i = 0;
    char *buffer;
    string_t strbuff;
    while (str->value[i]){
        idx++;
        buffer = string_slicing(str, i, str->len + i);
        strbuff = newstring(buffer);
        if (string_compare(&strbuff, s) == 0){
            free(buffer);
            freestring(&strbuff);
            return idx;
        }
        i++;
    }
    free(buffer);
    freestring(&strbuff);
    return str->len+1;
}


size_t string_find_last(string_t *str, char *s){
    size_t i = str->len - countlen(s);
    size_t j = 0;
    char *buffer;
    string_t strbuff;
    while (i != 0){
        buffer = string_slicing(str, i, str->len - j);
        strbuff = newstring(buffer);
        if (string_compare(&strbuff, s) == 0){
            free(buffer);
            freestring(&strbuff);
            return i;
        }
        i--;
        j++;
    }
    free(buffer);
    freestring(&strbuff);
    return str->len+1;
}
