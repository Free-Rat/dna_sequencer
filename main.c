#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#define CHAIN 10
#define PERFECT_SEQUENCE 509
#define NEGATIVE_ERRORS 200
#define POSITIVE_ERRORS 0
#define DATA_SIZE PERFECT_SEQUENCE + POSITIVE_ERRORS - NEGATIVE_ERRORS 

void print_chain(char chain[CHAIN]) {
	for (int h = 0; h < CHAIN; h++) {
		printf("[%i] %c ", h, chain[h]);
	}
}	

int encode_chain(char orginal[CHAIN]) {

	// print orgianl chain
	// print_chain(orginal);

	for (int i = 0; i < CHAIN; i++) {
		printf("[%i] %c ", i, orginal[i]);
		
	}

	return -1;
}

int main() {
    FILE *file;
    char line[CHAIN + 10];
    char data[DATA_SIZE][CHAIN];
	int encoded_data [DATA_SIZE];
	
    // Open the file in read mode
    file = fopen("53.500-200", "r");

    // Check if the file opened successfully
    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    // Read data from the file line by line and store it in the array
    int i = 0;
    while (fgets(line, CHAIN + 10, file) != NULL) {
        strcpy(data[i], line);
        i++;
    }

    fclose(file);

    // Printing the data
  //   for (int j = 0; j < i; j++) {
  //       // printf("%s\n", data[j]);
		// for (int h = 0; h < CHAIN; h++) {
		// 	printf("[%i] %c ", h, data[j][h]);
		// }
		// printf("\n");
  //   }
	
	printf("data size: %d\n", DATA_SIZE);
	printf("size of chain %lu\n",
		sizeof(data[DATA_SIZE - 1])/
		sizeof(data[DATA_SIZE - 1][0]));

	// print last element
	// for (int j = 0; j < CHAIN; j++) {
	// 	printf("[%i] %c ", j, data[300 - 1][j]);
	// }

    return 0;
}
