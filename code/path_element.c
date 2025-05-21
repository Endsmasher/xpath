#define _GNU_SOURCE
#include "path_element.h"
#include <stdio.h>

PathElement *createPathElement(const char *type, String id, String class[], const int class_count, PathElement *parent) {
  PathElement *element = malloc(sizeof(PathElement));
    if (!element) return NULL;
    element->type.str = NULL;
    element->id.str = NULL;
    element->class = NULL;
    element->class_count = 0;
    element->children = NULL;
    element->children_count = 0;

    if (type != NULL) {
        element->type.str = strdup(type);
        if (!element->type.str) {
            free(element);
            return NULL;
        }
    }

    if (id.str != NULL) {
        element->id.str = strdup(id.str);
        if (!element->id.str) {
            free(element->type.str);
            free(element);
            return NULL;
        }
    }

    if (class != NULL && class_count > 0) {
        element->class_count = class_count;
        element->class = malloc(sizeof(String) * class_count);
        if (!element->class) {
            free(element->type.str);
            free(element->id.str);
            free(element);
            return NULL;
        }
        for (int i = 0; i < class_count; i++) {
            element->class[i].str = strdup(class[i].str);
            if (!element->class[i].str) {
                for (int j = 0; j < i; j++) {
                    free(element->class[j].str);
                }
                free(element->class);
                free(element->type.str);
                free(element->id.str);
                free(element);
                return NULL;
            }
        }
    }

    if (parent != NULL) {
        PathElement **new_children = realloc(parent->children, sizeof(PathElement *) * (parent->children_count + 1));
        if (!new_children) {
            for (int i = 0; i < element->class_count; i++) {
                free(element->class[i].str);
            }
            free(element->class);
            free(element->type.str);
            free(element->id.str);
            free(element);
            return NULL;
        }
        parent->children = new_children;
        parent->children[parent->children_count] = element;
        parent->children_count++;
    }

    return element;
}

void freePathElements(PathElement *element) {
  if (!element) return;

    if (element->type.str)
        free(element->type.str);

    if (element->id.str)
        free(element->id.str);

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

void printPathElements(PathElement *element, const int level) {
   if (!element) return;

    for (int i = 0; i < level; i++) {
        printf("  ");
    }

    printf("Type: %s\n", element->type.str ? element->type.str : "(null)");

    if (element->id.str != NULL) {
        for (int i = 0; i < level; i++) printf("  ");
        printf("IDs: %s\n", element->id.str);
    }

    if (element->class_count > 0) {
        for (int i = 0; i < level; i++) printf("  ");
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