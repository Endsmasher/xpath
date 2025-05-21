//
// Created by Joshua on 13.05.2025.
//

#include "helper.h"

String *charToStr(char *s) {
  if (s == NULL) return NULL;

  String *result = malloc(sizeof(String));
  if (!result) return NULL;

  result->str = malloc(strlen(s) + 1);
  if(!result->str) {
    free(result);
    return NULL;
  }

  strncpy(result->str, s,  strlen(s));

  return result;
}

StringArray *charToStrArr(char *args, String *delim) {
  if (args == NULL) return NULL;

  char *args_copy = strdup(args);
  if (!args_copy) return NULL;

  StringArray *result = malloc(sizeof(StringArray));

  if (!result) {
    free(args_copy);
    return NULL;
  }

  result->string = NULL;
  result->count = 0;

  const char *token = strtok(args, delim->str);
  int i = 0;

  while (token != NULL) {
    result->string = realloc(result->string, sizeof(String)*(i + 1));
    if (!result->string) {
      freeStringArray(result);
      free(args_copy);
      return NULL;
    }

    result->string[i].str = strdup(token);
    if (!result->string[i].str) {
      freeStringArray(result);
      free(args_copy);
      return NULL;
    }

    i+=1;
    result->count = i;

    token = strtok(NULL, delim->str);
  }
  free(args_copy);

  return result;
}

void freeStringArray(StringArray *args) {
  if (args == NULL) return;

  for (int i = 0; i < args->count; i++) {
    free(args->string[i].str);
  }
  free(args->string);
  free(args);
}