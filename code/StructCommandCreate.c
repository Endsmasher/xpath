#include <stdio.h>
#include <string.h>
#include "helper.h"
#include "path_element.h"
#include "PathElement.c"

// body/div/div.id=343234.class=miau/div
// C:\Users\herbi\CLionProjects\xpath\html\test.txt div/div/div.id=22.class=a/div
// ./Programm "C:\Users\herbi\CLionProjects\xpath\html\test.txt div/div/div/price/id=223221/Auto"
// absolute path nötig aktuell

//Für die Ganze HTML sein dummy
void init_root(PathElement *root) {                                     //pointer auf ein pathelement adresse /  bekommt werte von pathelement
    strcpy_s(root->type, sizeof root->type, "Body");      //in die struct root in der type denn string "body" reingemacht also namen
    root->id            = NULL;
    root->id_count      = 0;
    root->class         = NULL;                                         //beabeten der struct sachen von struct root "->" = Zugriff
    root->class_count   = 0;
    root->children      = NULL;
    root->children_count= 0;
}

void Programm(char *file_path, size_t len, PathElement *parent){
    PathElement *current = parent;                                      // current bekommt die adresse parent //parent bleibt als save point aka 1 baum der erste
    // für denn file path
    printf("Programm start\n");
    printf("Bitte Zuerst denn dateipfad und dann denn path. Mit leerzeichen trennen: ");

    char eingabe[200];

    // noch ändern auf ohne limit
    fgets(eingabe, sizeof(eingabe), stdin);         //fgets liest alles ein inklusive leerzeichen "C:\\datei.txt\n\0" durch enter taste kommt \n \0 \dazu ( "miau.txt div/div/id=2343/div\n\0" )
    eingabe[strcspn(eingabe, "\n")] = '\0';       // strcspn(eingabe, "\n") gibt in welcher position in buffer \n befindet und macht dann daraus ein \0 bsp: eingabe[12] = '\0';  an pos 12 war das \n
                                                                // somit entfernen wird das new-line aus der ausgabe die in fget mit eingelesen worden ist.

    char *token = strtok(eingabe, " ");           // liest bis zum leerzeichen `\0` und gibt einen Zeiger auf token zurück ( token -> dateipfad )
    if (token != NULL) {                                    // prüft ob token auch wirklich gegeben ist ( falls nix dabei ist )
        strncpy(file_path, token, len-1);        //kopiert bis len-1 denn token nach file_path wieso ? um zu vermeiden das nach programm ende es geloscht wird len=200 sizeof in main also -1 für /0
        file_path[len-1] = '\0';                            //vermeided das token länger als ziel buffer ist
                                                            //füllt die restlichen zeilen mit null bytes aus + Das garantiert bei einem sehr langen token (länger als len-1) buffer weiterhin als C-String endet und kein Überlauf entsteht "ABCDEFGHI\0" len=10
    }
    else {
        Programm(file_path, len, parent);                           // falls kein token gegeben ist durch rekusion wieder neustart der funktion
    }
    printf("File-Path: %s\n", file_path);

    //Die elemetent paths
    //String *delim = charToStr(",");
    token = strtok(NULL, "/");                      // Oben schon deklariert und setzt die token einlesung fort
    String ids[1], classes[1];                   // current wanderer durch die ganzen children
    int id_count = 0, class_count = 0;              // jeder struct hat entwieder 1 id oder 1 Klasse aber nie beiedes gleichzeit = array größe 1
    char buff[200];

    while (token != NULL) {                             // Schleife um keine feste angegbene menge an paths zu haben
        if (sscanf(token, "id=%s", buff) == 1) {   // scant token, erwarte I,D,= und ließt eine zahl ( %d ) und speichert die in Id
            printf("Element-Pfad id: %s\n", buff);
            //idtokenstruct
            ids[0].str = strdup(buff);                    // nicht = weil sonst wird id.. id zugewissen aber wir wollen nur denn inhalt rein kopieren nicht die adresse kopieren
            id_count = 1;                               // sammelt daten und wenn unten ist macht es den struct daraus

        }else if (sscanf(token, "class=%s", buff) == 1) {
            printf("Element-Pfad class: %s\n", buff);
            classes[0].str = strdup(buff);
            class_count = 1;
        }
        else {
            printf("Element-Pfad: %s\n", token);
        }
        // nuer Knoten wird erstellt und als child an current
        PathElement *neues = createPathElement(
            token,           // hier Nutze für type am besten dasselbe token type = name
            ids,
            id_count,
            classes,     //erstellt aus denn daten das struct
            class_count,
            current);
        current = neues;    // neues wird zu current gemacht um es in der schleife zu bearbeiten
        token = strtok(NULL, "/");
    }
}
int Filereader (char *file_path, size_t len, PathElement *root){
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
            Programm(file_path, sizeof(file_path), root);  //(char *file_path, size_t len) übergebung der size und
        }
        return 0;
}

int main() {
    PathElement root;  //inizaliesierung von root
    init_root(&root);

    char file_path[200];
    Programm(file_path, sizeof(file_path), &root);
    Filereader(file_path, sizeof file_path, &root);
    printf("Baum: \n");
    printPathElements(&root, 0);
    freePathElements(&root);
    return 0;
}


//String *test = charToStr(eingabe);

//String *delim = charToStr(",");

//StringArray *test2 = charToStrArr(eingabe, delim);

//PathElement *test3 = CreatePathElement("", test2->string, test2->count, NULL, 0, NULL);