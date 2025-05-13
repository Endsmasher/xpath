#include <stdio.h>
#include <filepath_provider.h>


int main() {
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
        main();
    }
    return 0;
}
