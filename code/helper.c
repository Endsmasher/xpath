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

  strcpy_s(result->str, strlen(s), s);

  return result;
}

StringArray *charToStrArr(char *args, String *delim) {
  if (args == NULL) return NULL;                            // wenn args / eingabe = nichts ist wird NULL ausgegeben

  char *args_copy = _strdup(args);
  if (!args_copy) return NULL;                              //NULL wenn adresse args_copy kein string bekommen hat von args

  char *context = NULL;
  StringArray *result = malloc(sizeof(StringArray));    //reserviert ein heap speicher adresse malloc....größe byte stringarray  in pointer result

  if (!result) { //result == NULL
    free(args_copy);
    return NULL;      //bricht die funktion ab
  }

  result->string = NULL;
  result->count = 0;

  const char *token = strtok_s(args, delim->str, &context);
  int i = 0;

  while (token != NULL) {
    result->string = realloc(result->string, sizeof(String)*(i + 1));
    if (!result->string) {
      freeStringArray(result);
      free(args_copy);
      return NULL;
    }

    result->string[i].str = _strdup(token);
    if (!result->string[i].str) {
      freeStringArray(result);
      free(args_copy);
      return NULL;
    }

    i+=1;
    result->count = i;

    token = strtok_s(NULL, delim->str, &context);
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