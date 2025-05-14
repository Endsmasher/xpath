#include <path_element.h>

PathElement *createPathElement(char *type, String id[], int id_count, String class[], int class_count, PathElement *parent) {
  PathElement *element = malloc(sizeof(PathElement));

  strcpy_s(element->type, sizeof(element->type) + 1, type);

  element->id_count = id_count;
  element->id = malloc(sizeof(String) * id_count);

  for (int i = 0; i < id_count; i++) {
    element->id[i].str = _strdup(id[i].str);
  }

  element->class_count = class_count;
  element->class = malloc(sizeof(String) * class_count);

  for (int i = 0; i < class_count; i++) {
    element->class[i].str = _strdup(class[i].str);
  }

  parent->children = realloc(parent->children, sizeof(PathElement *) * (parent->children_count + 1));
  parent->children[parent->children_count] = element;
  parent->children_count += 1;

  return element;
}

void freePathElements(PathElement *element) {
  if (element == NULL) return;

  // Free IDs
  for (int i = 0; i < element->id_count; i++) {
    free(element->id[i].str);
  }
  free(element->id);

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