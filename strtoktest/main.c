#include <string.h>
#include <stdio.h>

// returns 1 if worked, 0 otherwise
int id_to_name(int ID, char* obuff) {
    int success = 1; 

    FILE* fp = fopen("test.csv", "r");
    if (fp == NULL) {
        printf("Failed to open file in func\n");
        success = 0;
    }

    // 62 is max length (including nl but not null) given max name length 50 (in src)
    char buf[63] = {'\0'};
    char* token;
    const char delim[2] = ",";
    
    // iterate through file's lines, tokenizing the csv.
    while(fgets(buf, 62, fp) != NULL) {
        token = strtok(buf, delim);

        while (token != NULL) {
            if (strcmp(token, "\n") != 0) {
                printf("%s\n", token);
            }
            // I don't get why we pass NULL here.
            token = strtok(NULL, delim);
        }
    }
    
    
    fclose(fp);
    return success;
}

int main() {
    int ID = 2;
    char name[50] = {'\0'};

    id_to_name(ID, name);

    return 0;
}
