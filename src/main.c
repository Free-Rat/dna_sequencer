#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../lib/globals.h"
#include "../lib/sequence_reader.c"

int main() {
    int* original_data = read_sequence(FILE_SOURCE);

    //printf("%d\n", compare_sequences(data[0], data[1]));

    //for (int i = 0; i < DATA_SIZE; i++) {
    //    printf("%s\n", convert_sequence_to_string(original_data[i]));
    //}

    DNASequence** population = create_population(original_data);
    for (int i = 0; i < POPULATION_SIZE; i++) {
        output_dna_sequence(population[i], 0);
    }
    
    free(original_data);
    return 0;
}