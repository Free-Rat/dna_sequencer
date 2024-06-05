#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../lib/globals.h"
#include "../lib/sequence_reader.c"

int main() {
    int* data = read_sequence(FILE_SOURCE);

    printf("%d\n", compare_sequences(data[0], data[1]));

    free(data);
    return 0;
}