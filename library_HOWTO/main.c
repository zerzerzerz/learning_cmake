#include "src/func.h"
#include <stdio.h>

int main(int argc, char **argv) {
    if(argc < 2) {
        printf("Usage: %s <name>\n", argv[0]);
        return 1;
    }
    print(argv[1]);
    return 0;
}
