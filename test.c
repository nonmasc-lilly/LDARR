#define LDARR_IMPLEMENTATION
#include "Ldarr.h"
#include <stdio.h>

int main(int argc, char **argv) {
    struct LR_darr il;
    unsigned int i;
    il = LR_create(sizeof(int), 16);
    for(i=0; i<30; i++) {
        LR_PUSH(&il, &i);
    }
    for(i=0; i<30; i++) {
        printf("%4X\n", LR_GET(il, i, unsigned int));
    }
    LR_destroy(&il);
}
