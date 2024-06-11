#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../lib/globals.h"
#include "../lib/sequence_reader.c"

int main() {
    srand(time(NULL));

    int* original_data = read_sequence(FILE_SOURCE);
    int* prepared_data = prepare_data(original_data);


    // Creates the population of DNA words, randomizes them and sorts them by fitness.
    DNASequence** population = create_population(prepared_data);
    for (int i = 0; i < GENERATIONS; i++) {
        for (int j = 0; j < POPULATION_SIZE; j++) {
            find_max_length_in_sequence(population[j]);
        }
        sort_population(population);
		
        // Merge lists
		for (int j = 0; j < ELITE_SIZE; j += 2) {
			recombine_sequences(population[j], population[j + 1]);
		}

        // Mutate
		for (int j = 0; j < POPULATION_SIZE; j++) {
			if (rand() % 100 < (MUTATION_RATE * 100)) {
		 				mutate_list(population[j]);
			}
		}

    }

	sort_population(population);

    // Print population[0]->sequences, because it's the best one.
	output_dna_sequence(population[0], 0);

    free(original_data);
    return 0;
}
