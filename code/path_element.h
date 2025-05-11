#include <stdio.h>
#define PATH_ELEMENT_H

typedef struct string {
  char *str;

} string;


typedef struct PathElement {
  char type[256];

  string **id;
  int id_count;

  string *class;
  int class_count;

  struct PathElement **children;
  int children_count;

} PathElement;

PathElement *CreatePathElement(char *type, string id[], int id_count, string class[], int class_count, PathElement *parent);