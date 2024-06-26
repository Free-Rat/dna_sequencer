#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../lib/globals.h"
#include "../lib/sequence_reader.c"

#define N 10
int main_loop() {
    int* original_data = read_sequence(FILE_SOURCE);
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

int main() {
    srand(time(NULL));

	int results[N];
	for (int i = 0; i < N; i++) {
		results[i] = main_loop();
	}
	int sum = 0;
	int max = 0;
	for (int i = 0; i < N; i++) {
		sum += results[i];
		if (results[i] > max) {
			max = results[i];
		}
	}

	printf("%d\n", sum / N);
	printf("%d\n", max);
	return 0;
}
