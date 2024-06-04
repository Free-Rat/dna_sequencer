#include "globals.h"
#include <stdio.h>

int get_sequence_number(char letter) {
    switch (letter) {
        case 'A':
            return SEQ_A;
        case 'C':
            return SEQ_C;
        case 'G':
            return SEQ_G;
        case 'T':
            return SEQ_T;
    }

    exit(NON_SEQ_LETTER);
    return -1;
}

int* read_sequence(char *filename) {
    FILE *file;
    file = fopen(filename, "r");

    int* data = malloc(DATA_SIZE * sizeof(int));
    int seq_num = 0;

    char line[STRING_SIZE];
    while (fgets(line, STRING_SIZE, file) != NULL) {
        int i = 0;
        int sequence = 0;
        while (line[i] != '\n' && line[i] != '\0') {
            sequence <<= SEQ_SIZE;
            sequence |= get_sequence_number(line[i]);
            i++;
        }
        data[seq_num] = sequence;
        seq_num++;
    }

    fclose(file);
    return data;
}