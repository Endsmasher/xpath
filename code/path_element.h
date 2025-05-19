#pragma once
#include "helper.h"
#define PATH_ELEMENT_H

typedef struct PathElement {
  char type[256];

  String id;

  String *class;
  int class_count;

  struct PathElement **children;
  int children_count;
} PathElement;

/*
 * create path element tree structure
 * type the type of the html element (div, body, header)
 * id array of strings containing the ids (custom css id tags specific to each website)
 * class array of string containing the classes of the html element
 * parent the parent object to properly connect the elements
 * RETURNS: a PathElement object with allocated memory
 */
PathElement *createPathElement(const char *type, String id, String class[], int class_count, PathElement *parent);

/*
 * unassigning memory from PathElements
 * all child elements of this element will be freed
 */
void freePathElements(PathElement *element);

/* To use: printPathElements(firstElement, 0) */
void printPathElements(PathElement *element, int level);