#include <stdio.h>

#include "globals.h"
#include "sequence_functions.c"

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

void set_letter_deleter() {
    int deleter = 0;
    for (int i = 0; i < SEQ_SIZE; i++) {
        deleter <<= 1;
        deleter |= 1;
    }

    letter_deleter = ~(deleter << SEQ_SIZE * (CHAIN - 1));
}

/// @brief Reads all the sequences from the specifed file, encodes them in binary and stores them in an array.
/// @param filename File from which to read the sequences.
/// @return An array of integers, each representing a sequence in binary.
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
    set_letter_deleter();
    return data;
}