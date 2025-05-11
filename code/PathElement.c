#include <path_element.h>

PathElement *CreatePathElement(char *type, string id[], int id_count, string class[], int class_count, PathElement *parent) {
  PathElement *element = malloc(sizeof(PathElement));

  strcpy_s(element->type, sizeof(element->type) - 1, type);

  element->id_count = id_count;
  element->id = malloc(sizeof(string) * id_count);

  for (int i = 0; i < id_count; i++) {
    element->id[i].str = _strdup(id[i].str);
  }

  element->class_count = class_count;
  element->class = malloc(sizeof(string) * class_count);

  for (int i = 0; i < class_count; i++) {
    element->class[i].str = _strdup(class[i].str);
  }

  parent->children = realloc(parent->children, sizeof(PathElement) * (parent->children_count + 1));
  parent->children[parent->children_count] = element;
  parent->children_count += 1;

  return element;
}