#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../lib/globals.h"
#include "../lib/sequence_reader.c"

#define N 10

int main_loop(char* file_name) {
    int* original_data = read_sequence(file_name);
    int* prepared_data = prepare_data(original_data);
    // Creates the population of DNA words, randomizes them and sorts them by fitness.
    DNASequence** population = create_population(prepared_data);
    for (int i = 0; i < GENERATIONS; i++) {

        for (int j = 0; j < POPULATION_SIZE; j++) {
            find_max_length_in_sequence(population[j]);
        }
        sort_population(population);
		if (DEBUG) {
			printf("Generation %d best lenght %d\n", i, population[0]->max_length);
		}
        // Merge lists
		for (int j = ELITE_SIZE; j < POPULATION_SIZE; j += 2) {
			recombine_sequences(population[j], population[j + 1]);
		}
        // Mutate
        mutate_population(population);
    }
	sort_population(population);
    // Print population[0]->sequences, because it's the best one.
	if (DEBUG) {
		output_dna_sequence(population[0], 0);
	}
	// printf("Best length: %d\n", population[0]->max_length);
    free(original_data);
	return population[0]->max_length;
}

int main(int argc, char *argv[]) {
    srand(time(NULL));

	int file_from_console = 0;
	if (argc < 2 && DEBUG) {
		printf("Usage: %s <file_name>\n", argv[0]);
		file_from_console = 1;
		return 1;
	}

	int results[N];
	for (int i = 0; i < N; i++) {
		results[i] = main_loop(file_from_console ? argv[1] : FILE_SOURCE);
	}
	int sum = 0;
	int max = 0;
	for (int i = 0; i < N; i++) {
		sum += results[i];
		if (results[i] > max) {
			max = results[i];
		}
	}

	printf("Average: %d\n", sum / N);
	printf("Max: %d\n", max);
	return 0;
}
