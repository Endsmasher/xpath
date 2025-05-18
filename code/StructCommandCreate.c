//
// Created by herbi on 15.05.2025.
//
#include <stdio.h>
#include "helper.h"
#include "path_element.h"
//#include <filepath_provider.h>


// ./Programm "C:\Users\herbi\CLionProjects\xpath\html\test.txt div/div/div/price/id=223221/Auto"
// absolute path nötig aktuell


void Programm(char *file_path, size_t len){
    char eingabe[200];
    char class[20];
    char rawid[20];// noch ändern auf ohne limit


    // für denn file path
    printf("Programm start\n");
    printf("Bitte Zuerst denn dateipfad und dann denn path. Mit leerzeichen trennen: ");

    fgets(eingabe, sizeof(eingabe), stdin);       //fgets liest alles ein inklusive leerzeichen "C:\\datei.txt\n\0" durch enter taste kommt \n \0 \dazu ( "miau.txt div/div/id=2343/div\n\0" )
    eingabe[strcspn(eingabe, "\n")] = '\0';       // strcspn(eingabe, "\n") gibt in welcher position in buffer \n befindet und macht dann daraus ein \0 bsp: eingabe[12] = '\0';  an pos 12 war das \n

    String *delim = charToStr(" ");
    StringArray *outertoken = charToStrArr(eingabe, delim);

    printf("DateiPfad: %s\n", outertoken->string[0].str);
    strcpy(file_path, outertoken->string[0].str);

    String *deliminner= charToStr("/"); //!! ich würde hier einfach delim überschreiben anstelle einer neuen variable einzufügen !!
    StringArray *token= charToStrArr(outertoken->string[1].str, deliminner);
    PathElement *parent = createPathElement (token->string[0].str, NULL,0,NULL,0,NULL); //!! hier ist nur die parent zwingend null der rest ist nich umbedingt null !!

    for (int i = 1; i < token->count; i++) {
        if (token->string[i].str) {        // prüfung ob token überhaupt da ist
            if (strstr(token->string[i].str, "&") != NULL) {       // wenn ein token das symbol "&" enthält, dann soll token in der einzelne innertoken geteilt werden
                String *innertrenner = charToStr("&");
                StringArray *innertoken = charToStrArr(token->string[i].str, innertrenner);
                for (int t = 0; t < innertoken->count; t++) {
                    if (sscanf(innertoken->string[t].str, "id=%s", &rawid) == 1) { //!! hier das problem nur die erste id wird genommen also wenn es id=hallo hallo hallo ist beinhaltet rawid danach nur hallo !!
                        PathElement *child = createPathElement("",token->string,token->count,NULL,0,parent);
                    }else if (sscanf(innertoken->string[t].str, "class=%s", &class)) {
                        //!! selbige hier !!
                        PathElement *child = createPathElement("",NULL,0,token->string,token->count,child);
                    }else {
                        PathElement *childparent = createPathElement (token->string[t].str,NULL,0,NULL,0,parent);
                        parent = childparent; //für verzweigungen des type/childparents
                    }
                }
                freeStringArray(innertoken);
                }
            }
// wenn oben nein dann :
            if (sscanf(token->string[i].str, "id=%s", &rawid) == 1) { //!! hier das problem nur die erste id wird genommen also wenn es id=hallo hallo hallo ist beinhaltet rawid danach nur hallo !!
                PathElement *child = createPathElement("",token->string,token->count,NULL,0,parent);
            }else if (sscanf(token->string[i].str, "class=%s", &class)) { //!! selbige hier !!
                PathElement *child = createPathElement("",NULL,0,token->string,token->count,child);
                /* Bin mir nicht ganz sicher was du meinst, aber hier müsste sich für jeden children der parent ändern, wenn du jedem children den selben parent gibt dann ist es keine linie nach unten sondern idk ein 1 parent zu 20
                 * du müsstest einmal eine variable haben die den allerersten parent abspeichert (den musst du später mir zum vergleichen dann geben)
                 * und eine parent variable die sich konstant ändert, also wenn es div/hallo/ballo ist ist div am anfang die parent, sobald hallo erstellt wurde wird hallo zum parent, selbiges mit ballo, identisch zu einer verketteten liste
                 */
            }else {
                PathElement *childparent = createPathElement (token->string[i].str,NULL,0,NULL,0,parent);
                parent = childparent;
            }
        }


    printPathElements(parent, 0); //Ab welchen lvl der Baum geprintet wird
    freeStringArray(outertoken);
    freeStringArray(token);

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
