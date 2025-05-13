#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <path_element.h>

// ./Programm "../Pages/Seite.html div/div/div/price/id=223221/Auto"


void Programm(){
    // für denn file path
    printf("Programm start\n");
    printf("Bitte Zuerst denn dateipfad und dann denn path. Mit leerzeichen trennen: ");
    char eingabe[200];
    fgets(eingabe, sizeof(eingabe)-1, stdin);  //fgets liest alles ein inklusive leerzeichen
    char *file_path = strtok(eingabe, " ");
    printf("File-Path: %s\n", file_path);

    //Die elemetent paths
    char *token = strtok(NULL, "/");
    while (token != NULL) {
        printf("Element-Pfad: %s\n", token);
        token = strtok(NULL, "/");
    }
}
int main() {
    Programm();
    return 0;
}


