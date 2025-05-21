//
// Created by herbi on 15.05.2025.
//
#include <stdio.h>
#include "helper.h"
#include "path_element.h"
//#include <filepath_provider.h>


// ./Programm "C:\Users\herbi\CLionProjects\xpath\html\test.txt div/div/div/price/id=223221/Auto"
// absolute path nötig aktuell


void Programm(char *file_path, size_t len) {
    char eingabe[200];

    // für denn file path
    printf("Programm start\n");
    printf("Bitte Zuerst denn dateipfad und dann denn path. Mit leerzeichen trennen: ");

    fgets(eingabe, sizeof(eingabe), stdin);       //fgets liest alles ein inklusive leerzeichen "C:\\datei.txt\n\0" durch enter taste kommt \n \0 \dazu ( "miau.txt div/div/id=2343/div\n\0" )
    eingabe[strcspn(eingabe, "\n")] = '\0';       // strcspn(eingabe, "\n") gibt in welcher position in buffer \n befindet und macht dann daraus ein \0 bsp: eingabe[12] = '\0';  an pos 12 war das \n

    String *delim = charToStr("?");
    StringArray *outertoken = charToStrArr(eingabe, delim);

    printf("DateiPfad: %s\n", outertoken->string[0].str);
    strcpy(file_path, outertoken->string[0].str);

    String *deliminner= charToStr("/"); //!! ich würde hier einfach delim überschreiben anstelle einer neuen variable einzufügen !!
    StringArray *token= charToStrArr(outertoken->string[1].str, deliminner);
    PathElement *parent; //inizialisierung von parent für root uns co
    for (int i = 0; i < token->count; i++) {

        if (i == 0) { //für das erste/ Root und auch speichernd
            if (strstr(token->string[i].str, "&") != NULL) {// wenn ein token das symbol "&" enthält, dann soll token in der einzelne innertoken geteilt werden

                String *innertrenner = charToStr("&");
                StringArray *innertoken = charToStrArr(token->string[i].str, innertrenner);

                String *idtrenner = charToStr("id=");
                StringArray *rawid = charToStrArr(innertoken->string[1].str, idtrenner);    // nimmt das "Id=" aus dem 2 teil des innertoken also "div id=2323 clas=Auto Auto" == 2323 und speicher in rawid adresse

                String *classtrenner = charToStr("class=");
                StringArray *rawclasses = charToStrArr(innertoken->string[2].str, classtrenner);

                PathElement *root = createPathElement (innertoken->string[0].str, rawid->string[0],rawclasses->string,rawclasses->count,parent);
                parent = root;

                freeStringArray(rawclasses);
                freeStringArray(rawid);
                freeStringArray(innertoken);
            }else {
                PathElement *root = createPathElement (token->string[0].str,(String){ .str = NULL },NULL,0,NULL);
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

                PathElement *childparent = createPathElement (innertoken->string[0].str, rawid->string[0],rawclasses->string,rawclasses->count,parent);
                parent = childparent;

                freeStringArray(rawclasses);
                freeStringArray(rawid);
                freeStringArray(innertoken);
            }else {
                PathElement *childparent = createPathElement (token->string[i].str,(String){ .str = NULL },NULL,0,parent);  // id wird leerem wert übergeben
                parent = childparent; //für verzweigungen des type/childparent

            }

        }
    }
    freeStringArray(token);
    printPathElements(parent, 0); //Ab welchen lvl der Baum geprintet wird // Muss root sein but dawg zu müde
}

//            String *delim = charToStr("&");
//            StringArray *innertoken = charToStrArr(token->string[i].str, delim);

int Filereader(char *file_path) {
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
