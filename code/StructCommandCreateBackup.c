//
// Created by herbi on 15.05.2025.
//
#include <stdio.h>
#include <string.h>
#include <helper.h>
//#include <path_element.h>
//#include <filepath_provider.h>


// ./Programm "C:\Users\herbi\CLionProjects\xpath\html\test.txt div/div/div/price/id=223221/Auto"
// absolute path nötig aktuell


void Programm(char *file_path, size_t len){
    // für denn file path
    printf("Programm start\n");
    printf("Bitte Zuerst denn dateipfad und dann denn path. Mit leerzeichen trennen: ");

    char eingabe[200];                            // noch ändern auf ohne limit
    fgets(eingabe, sizeof(eingabe), stdin);       //fgets liest alles ein inklusive leerzeichen "C:\\datei.txt\n\0" durch enter taste kommt \n \0 \dazu ( "miau.txt div/div/id=2343/div\n\0" )
    eingabe[strcspn(eingabe, "\n")] = '\0';       // strcspn(eingabe, "\n") gibt in welcher position in buffer \n befindet und macht dann daraus ein \0 bsp: eingabe[12] = '\0';  an pos 12 war das \n
                                                  // somit entfernen wird das new-line aus der ausgabe die in fget mit eingelesen worden ist.


    char *token = strtok(eingabe, " ");           // liest bis zum leerzeichen `\0` und gibt einen Zeiger auf token zurück ( token -> dateipfad )
    if (token != NULL) {                          // prüft ob token auch wirklich gegeben ist ( falls nix dabei ist )
        strncpy(file_path, token, len-1);        //kopiert bis len-1 denn token nach file_path wieso ? um zu vermeiden das nach programm ende es geloscht wird len=200 also -1 für /0
        file_path[len-1] = '\0';                  //vermeided das token länger als ziel buffer ist
                                                  //füllt die restlichen zeilen mit null bytes aus + Das garantiert bei einem sehr langen token (länger als len-1) buffer weiterhin als C-String endet und kein Überlauf entsteht "ABCDEFGHI\0" len=10
    }
    else {
        Programm(file_path, len);                 // falls kein token gegeben ist durch rekusion wieder neustart der funktion
    }
    printf("File-Path: %s\n", file_path);

    //Die elemetent paths
    //String *delim = charToStr(",");
    token = strtok(NULL, "/");                    // Oben schon deklariert und setzt die token einlesunf fort
    while (token != NULL) {                       // Schleife um keine feste angegbene menge an paths zu haben
        char id[200];
        if (sscanf(token, "id=%s", &id) == 1) {   // scant token, erwarte I,D,= und ließt eine zahl ( %d ) und speichert die in Id
            printf("Element-Pfad id: %s\n", id);
        }
        else {
            printf("Element-Pfad: %s\n", token);
        }
        token = strtok(NULL, "/");
    }
}


int Filereader (char *file_path){
        FILE *file;


        file = fopen(file_path, "r");
        char buffer[1024];
        if(file != NULL){
            while (fgets(buffer, sizeof(buffer), file) != NULL) {
                printf("File opened: %s\n", buffer);
            }
            fclose(file);
        }
        else{
            printf("File Not Found\n");
            Programm(file_path, sizeof(file_path));  //(char *file_path, size_t len) übergebung der size und
        }
        return 0;
}

int main() {
    char file_path[200];
    Programm(file_path, sizeof(file_path));
    Filereader(file_path);
    return 0;
}


//String *test = charToStr(eingabe);

//String *delim = charToStr(",");

//StringArray *test2 = charToStrArr(eingabe, delim);

//PathElement *test3 = CreatePathElement("", test2->string, test2->count, NULL, 0, NULL);