/*
 * Helper class to allocate String and other similar structs memory and free it again
 */
#pragma once
#include <stdlib.h>
#include <string.h>

typedef struct String {
  char *str;
} String;

typedef struct StringArray {
  String *string;
  int count;

} StringArray;
/* Create new object StringArray
 * args to create from
 * delim what to separate every string from each other
 * RETURNS: NULL if args is empty, invalid or no memory could be allocated
 * RETURNS: Pointer to StringArray, which contains count of elements and array
 */
StringArray *charToStrArr(char *args, String *delim);
/* Create new string from char pointer
 * s is the char which will be transformed to a string
 * RETURNS: NULL if s is null or no memory could be allocated during process
 */
String *charToStr(char *s);

/* Free memory used for StringArray */
void freeStringArray(StringArray *arg);