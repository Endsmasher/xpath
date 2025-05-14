#include <stdio.h>
#include <string.h>
//#include <helper.h>
//#include <path_element.h>

// ./Programm "C:\\Users\\herbi\\CLionProjects\\xpath\\html\\test.txt div/div/div/price/id=223221/Auto"
// absolute path nötig aktuell


void Programm(){
    // für denn file path
    printf("Programm start\n");
    printf("Bitte Zuerst denn dateipfad und dann denn path. Mit leerzeichen trennen: ");
    char eingabe[200];  // noch ändern auf ohne limit
    fgets(eingabe, sizeof(eingabe)-1, stdin);  //fgets liest alles ein inklusive leerzeichen
    char *file_path = strtok(eingabe, " ");
    printf("File-Path: %s\n", file_path);

    //Die elemetent paths
    //String *delim = charToStr(",");
    char *token = strtok(NULL, "/");
    while (token != NULL) {
        int id;
        if (sscanf(token, "id=%d", &id) == 1) {   // scant token, erwarte I,D,= und ließt eine zahl ( %d ) und speichert die in Id
            printf("Element-Pfad id: %d\n", id);
        }
        else {
            printf("Element-Pfad: %s\n", token);
        }
        token = strtok(NULL, "/");
    }
}
int main() {
    Programm();
    return 0;
}


//String *test = charToStr(eingabe);

//String *delim = charToStr(",");

//StringArray *test2 = charToStrArr(eingabe, delim);

//PathElement *test3 = CreatePathElement("", test2->string, test2->count, NULL, 0, NULL);