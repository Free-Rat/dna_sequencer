#include <string.h>

#include "globals.h"

int letter_size;
int letter_deleter;

typedef struct DNASequence {
    int** sequences;
    int from;
    int to;
	int max_length;
}DNASequence;

// implementation of quicksort algorithm for sorting the population
void swap(DNASequence* a, DNASequence* b) {
	DNASequence temp = *a;
	*a = *b;
	*b = temp;
}

int partition(DNASequence* population[], int low, int high) {
	int pivot = population[high]->max_length;
	int i = low - 1;
	for (int j = low; j <= high - 1; j++) {
		if (population[j]->max_length > pivot) {
			i++;
			swap(population[i], population[j]);
		}
	}
	swap(population[i + 1], population[high]);
	return i + 1;
}

void quicksort(DNASequence* population[], int low, int high) {
	if (low < high) {
		int pi = partition(population, low, high);
		quicksort(population, low, pi - 1);
		quicksort(population, pi + 1, high);
	}
}

DNASequence** sort_population(DNASequence* population[]) {
	quicksort(population, 0, POPULATION_SIZE - 1);
	return population;
}

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
