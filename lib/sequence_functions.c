#include <string.h>

#include "globals.h"

int letter_size;
int letter_deleter;

struct dnaSequence {
	int max_length;
};
	

char *strrev(char *str)
{
      char *p1, *p2;

      if (! str || ! *str)
            return str;
      for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
      {
            *p1 ^= *p2;
            *p2 ^= *p1;
            *p1 ^= *p2;
      }
      return str;
}

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

char get_sequence_letter(int coded_letter) {
    switch (coded_letter) {
        case SEQ_A:
            return 'A';
        case SEQ_C:
            return 'C';
        case SEQ_G:
            return 'G';
        case SEQ_T:
            return 'T';
    }

    exit(NON_SEQ_LETTER);
    return -1;
}

/// @brief Compares two sequences and checks whether a series can be created from them. The order of given arguments matters.
/// @param seq1 First sequence to compare.
/// @param seq2 Second sequence to compare.
/// @return 0 if a series can be created from the sequences, 1 otherwise.
int compare_sequences(int seq1, int seq2) {
    return (seq1 & letter_deleter) == (seq2 >> SEQ_SIZE);
}

char* convert_sequence_to_string(int sequence) {
    char* string = malloc(STRING_SIZE * sizeof(char));

    int i;
    for (i = 0; i < CHAIN; i++) {
        string[i] = get_sequence_letter(sequence & letter_size);
        sequence >>= SEQ_SIZE;
    }

    string[i] = '\0';
    strrev(string);
    return string;
}
