#include <stdio.h>

int main() {
    char data[33];

    FILE* p  = popen("cat /dev/ttyACM0", "r");
    if (!p) {
        puts("could not open process");
        return 1;
    }

    fgets(data, 33, p);

    printf("%s\n", data);

    puts("done");

    if (pclose(p) == -1) {
        puts("could not close process");
    }

    return 0;
}
