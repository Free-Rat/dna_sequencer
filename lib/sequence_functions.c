#include <string.h>

#include "globals.h"

/// @brief With bitwise AND can delete the youngest bits of a sequence.
int young_letter_deleter;

/// @brief With bitwise AND can delete the oldest bits of a sequence.
int old_letter_deleter;

int* removed_sequences = NULL;

typedef struct DNASequence {
    int** sequences;
    int from;
    int to;
	int max_length;
} DNASequence;

/// @brief Compares two sequences and checks whether a series can be created from them. The order of given arguments matters.
/// @param seq1 First sequence to compare.
/// @param seq2 Second sequence to compare.
/// @return 0 if a series can be created from the sequences, 1 otherwise.
int compare_sequences(int seq1, int seq2) {
    return (seq1 & old_letter_deleter) == (seq2 >> SEQ_SIZE);
}

// implementation of quicksort algorithm for sorting the population
void swap(DNASequence** a, DNASequence** b) {
	DNASequence* temp = *a;
	*a = *b;
	*b = temp;
}

void swap_int(int** a, int** b) {
    int* temp = *a;
    *a = *b;
    *b = temp;
}

int partition(DNASequence* population[], int low, int high) {
	int pivot = population[high]->max_length;
	int i = low - 1;
	for (int j = low; j <= high - 1; j++) {
		if (population[j]->max_length > pivot) {
			i++;
			swap(&population[i], &population[j]);
		}
	}
	swap(&population[i + 1], &population[high]);
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

char* convert_sequence_to_string(int sequence) {
    char* string = malloc(STRING_SIZE * sizeof(char));

    int i;
    for (i = 0; i < CHAIN; i++) {
        string[i] = get_sequence_letter(sequence & young_letter_deleter);
        sequence >>= SEQ_SIZE;
    }

    string[i] = '\0';
    strrev(string);
    return string;
}

void init_dna_sequences(DNASequence* dna_sequence, int* data) {
    dna_sequence->sequences = malloc(PERFECT_SEQUENCE * sizeof(int*));
    dna_sequence->from = 0;
    dna_sequence->to = 0;
    dna_sequence->max_length = 0;

    for (int i = 0; i < PERFECT_SEQUENCE; i++) {
        dna_sequence->sequences[i] = &data[i];
    }
}

int normalize_index(int i) {
    if (i < 0) {
        return 0;
    }
    else if (i >= PERFECT_SEQUENCE) {
        return PERFECT_SEQUENCE - 1;
    }

    return i;
}

void randomize_list(int** sequences) {
    for (int i = 0; i < PERFECT_SEQUENCE; i++) {
        if (rand() % 2) {
            int move = rand() % (PERFECT_SEQUENCE * 2) - PERFECT_SEQUENCE;
            int index = normalize_index(i + move);
            swap_int(&sequences[i], &sequences[index]);
        }
    }
}

void swap_int_simple(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void randomize_list_simple(int* sequences) {
    for (int i = 0; i < PERFECT_SEQUENCE; i++) {
        if (rand() % 2) {
            int move = rand() % (PERFECT_SEQUENCE * 2) - PERFECT_SEQUENCE;
            int index = normalize_index(i + move);
            swap_int_simple(&sequences[i], &sequences[index]);
        }
    }
}

void find_max_length_in_sequence(DNASequence* dna_sequence) {
    int length = 0;
    int max_length = 0;

    int potential_from = 0;
    int from = 0;
    int to = 0;
    int i;
    for (i = 0; i < PERFECT_SEQUENCE; i++) {
        if (i == 0 || compare_sequences(*dna_sequence->sequences[i], *dna_sequence->sequences[i - 1])) {
            length++;
        }
        else {
            if (length > max_length) {
                max_length = length;
                from = potential_from;
                to = i;
            }
            potential_from = i + 1;
            length = 1;
        }
    }

    if (length > max_length) {
        max_length = length;
        to = i - 1;
    }

    dna_sequence->max_length = max_length;
    dna_sequence->from = from;
    dna_sequence->to = to;
}

DNASequence** create_population(int* data) {
    DNASequence* population = malloc(POPULATION_SIZE * sizeof(DNASequence));
    DNASequence** population_ptr = malloc(POPULATION_SIZE * sizeof(DNASequence*));
    for (int i = 0; i < POPULATION_SIZE; i++) {
        population_ptr[i] = &population[i];
        init_dna_sequences(population_ptr[i], data);
        randomize_list(population_ptr[i]->sequences);
    }

    return population_ptr;
}

int* copy_array(int* data, int new_size) {
    int* new_data = malloc(new_size * sizeof(int));
    for (int i = 0; i < DATA_SIZE; i++) {
        new_data[i] = data[i];
    }

    return new_data;
}

int generate_random_sequence() {
    int max_seq_val = (1 << CHAIN * SEQ_SIZE) - 1;
    return rand() % max_seq_val;
}

void insert_seq(int* data, int index) {
    int inserted = 0;
    int generated_seq;
    while (!inserted) {
        generated_seq = generate_random_sequence();
        inserted = 1;
        for (int i = 0; i < DATA_SIZE; i++) {
            if (generated_seq == data[i]) {
                inserted = 0;
                break;
            }
        }
    }

    data[index] = generated_seq;
}

void mutate_list(DNASequence* dna_sequence) {
    
}

void mutate_population(DNASequence** population) {

}

int* prepare_data(int* data) {
    int* new_data;
    if (NEGATIVE_ERRORS > 0) {
        new_data = copy_array(data, PERFECT_SEQUENCE);
        for (int i = DATA_SIZE; i < PERFECT_SEQUENCE; i++) {
            insert_seq(new_data, i);
        }
    }
    else if (POSITIVE_ERRORS > 0) {
        randomize_list_simple(data);
        new_data = copy_array(data, PERFECT_SEQUENCE);
        removed_sequences = copy_array(&data[PERFECT_SEQUENCE], POSITIVE_ERRORS);
    }
    else {
        new_data = copy_array(data, DATA_SIZE);
    }

    return new_data;
}

void output_dna_sequence(DNASequence* dna_sequence, int binary) {
    for (int i = 0; i < DATA_SIZE; i++) {
        if (binary) {
            printf("%d\n", *dna_sequence->sequences[i]);
        }
        else {
            printf("%s\n", convert_sequence_to_string(*dna_sequence->sequences[i]));
        }
    }
}
