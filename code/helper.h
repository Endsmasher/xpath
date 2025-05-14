/*
 * Helper class to allocate String and other similar structs memory and free it again
 */

#include <stdlib.h>
#include <string.h>
#define HELPER_H

typedef struct String {
  char *str;
} String;

typedef struct StringArray {
  String *string;
  int count;

} StringArray;
/* Create new object StringArray */
StringArray *charToStrArr(char *args, String *delim);
/* Create new string from char pointer */
String *charToStr(char *s);

/* Free memory used for StringArray */
void freeStringArray(StringArray *arg);