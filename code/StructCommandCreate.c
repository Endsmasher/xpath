//
// Created by herbi on 15.05.2025.
//
#include <stdbool.h>
#include <stdio.h>
#include "helper.h"
#include "path_element.h"
#include "headargp.h"
//#include <filepath_provider.h>


// ./Programm "C:\Users\herbi\CLionProjects\xpath\html\test.txt div/div/div/price/id=223221/Auto"
// absolute path nötig aktuell
// test.txt?div/div/div&id=343234&class=auto auto moew/div

void Programm(char *file_path, char *path) {

    // für denn file path
    printf("DateiPfad: %s\n", file_path);

    String *deliminner= charToStr("/"); //!! ich würde hier einfach delim überschreiben anstelle einer neuen variable einzufügen !!
    StringArray *token= charToStrArr(path, deliminner);

    PathElement *root = NULL;
    PathElement *parent = root;

    for (int i = 0; i < token->count; i++) {

        if (i == 0) { //für das erste/ Root und auch speichernd
            if (strstr(token->string[i].str, "&") != NULL) {// wenn ein token das symbol "&" enthält, dann soll token in der einzelne innertoken geteilt werden

                String *innertrenner = charToStr("&");
                StringArray *innertoken = charToStrArr(token->string[i].str, innertrenner);

                String *idtrenner = charToStr("id=");
                StringArray *rawid = charToStrArr(innertoken->string[1].str, idtrenner);    // nimmt das "Id=" aus dem 2 teil des innertoken also "div id=2323 clas=Auto Auto" == 2323 und speicher in rawid adresse

                String *classtrenner = charToStr("class=");
                StringArray *rawclasses = charToStrArr(innertoken->string[2].str, classtrenner);
                root = createPathElement (innertoken->string[0].str, rawid->string[0],rawclasses->string,rawclasses->count, NULL);
                parent = root;

                freeStringArray(rawclasses);
                freeStringArray(rawid);
                freeStringArray(innertoken);
            }else {
                root = createPathElement (token->string[0].str,(String){ .str = NULL },NULL,0,NULL);
                parent = root;
            }
            i++;
        }
        if (token->string[i].str) {        // prüfung ob token überhaupt da ist
            if (strstr(token->string[i].str, "&") != NULL) {// wenn ein token das symbol "&" enthält, dann soll token in der einzelne innertoken geteilt werden

                String *innertrenner = charToStr("&");
                StringArray *innertoken = charToStrArr(token->string[i].str, innertrenner);

                String *idtrenner = charToStr("id=");
                StringArray *rawid = charToStrArr(innertoken->string[1].str, idtrenner);    // nimmt das "Id=" aus dem 2 teil des innertoken also "div id=2323 clas=Auto Auto" == 2323 und speicher in rawid adresse

                String *classtrenner = charToStr("class=");
                StringArray *rawclasses = charToStrArr(innertoken->string[2].str, classtrenner);

                parent = createPathElement (innertoken->string[0].str, rawid->string[0],rawclasses->string,rawclasses->count,parent);

                freeStringArray(rawclasses);
                freeStringArray(rawid);
                freeStringArray(innertoken);
            }else {
                parent = createPathElement (token->string[i].str,(String){ .str = NULL },NULL,0,parent);  // id wird leerem wert übergeben
            }
        }
    }
    freeStringArray(token);
    printPathElements(root, 0);

}

//            String *delim = charToStr("&");
//            StringArray *innertoken = charToStrArr(token->string[i].str, delim);

int Filereader(const char *file_path) {
    FILE *file = fopen(file_path, "r");
    if (!file) {
        fprintf(stderr, "Fehler: Datei '%s' nicht gefunden\n", file_path);
        return -1;
    }
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf(">> %s", buffer);
    }
    fclose(file);
    return 0;
}

int main(int argc, char **argv) {
    if (parse_cmdline(argc, argv) != 0)   // ungültige eingaben prüfen // in die globale Struktur arguments
        return 1;
    Programm(arguments.file_path, arguments.path);
	Filereader(arguments.file_path);
    return 0;
}