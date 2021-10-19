#include <stdio.h>

#define SIZE_OF(type) (printf("sizeof(" #type ") = %d\n", sizeof(type)))

int main() {
    SIZE_OF(char);
    SIZE_OF(short);
    SIZE_OF(int);
    SIZE_OF(long);
    SIZE_OF(long long);
    SIZE_OF(float);
    SIZE_OF(double);
    SIZE_OF(long double);
    SIZE_OF(unsigned long);
    return 0;
}
