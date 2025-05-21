#define _GNU_SOURCE
#include "path_element.h"
#include <stdio.h>

PathElement *createPathElement(const char *type, String id, String class[], const int class_count, PathElement *parent) {
  PathElement *element = malloc(sizeof(PathElement));

  strncpy(element->type.str, type, sizeof(element->type) + 1);
  strncpy(element->id.str, id.str, sizeof(element->id) + 1);

  element->class_count = class_count;
  element->class = malloc(sizeof(String) * class_count);

  for (int i = 0; i < class_count; i++) {
    element->class[i].str = strdup(class[i].str);
  }

  parent->children = realloc(parent->children, sizeof(PathElement *) * (parent->children_count + 1));
  parent->children[parent->children_count] = element;
  parent->children_count += 1;

  return element;
}

void freePathElements(PathElement *element) {
  if (!element) return;

  for (int i = 0; i < element->class_count; i++) {
    free(element->class[i].str);
  }
  free(element->class);

  for (int i = 0; i < element->children_count; i++) {
    freePathElements(element->children[i]);
  }
  free(element->children);

  free(element);
}


void printIndent(int level) {
  for (int i = 0; i < level; i++) {
    printf("  "); // 2 spaces x level
  }
}

void printPathElements(PathElement *element, const int level) {
  if (!element) return;

  printIndent(level);
  printf("Type: %s\n", element->type);

  if (element->id.str != NULL) {
    printIndent(level);
    printf("IDs: ");
    printf("%s", element->id.str);

    printf("\n");
  }

  if (element->class_count > 0) {
    printIndent(level);
    printf("Classes: ");
    for (int i = 0; i < element->class_count; i++) {
      printf("%s", element->class[i].str);
      if (i < element->class_count - 1) printf(", ");
    }
    printf("\n");
  }

  for (int i = 0; i < element->children_count; i++) {
    printPathElements(element->children[i], level + 1);
  }
}