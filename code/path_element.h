#pragma once
#include <helper.h>
#define PATH_ELEMENT_H

typedef struct PathElement {
  char type[256];

  String *id;
  int id_count;

  String *class;
  int class_count;

  struct PathElement **children;
  int children_count;
} PathElement;

PathElement *CreatePathElement(char *type, String id[], int id_count, String class[], int class_count, PathElement *parent);

void FreePathElement(PathElement *element);

void FreePathElementWithChildren(PathElement *element);