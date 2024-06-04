#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../lib/globals.h"
#include "../lib/sequence_reader.c"

int main() {
    int* data = read_sequence(FILE_SOURCE);
	for (int i = 0; i < DATA_SIZE; i++) {
        printf("%d\n", data[i]);
    }

    free(data);
    return 0;
}