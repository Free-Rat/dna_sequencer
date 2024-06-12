#!/bin/bash

# Directory containing the text files
DIR="res"

# Output directory for the compiled program
BUILD_DIR="build"
EXECUTABLE="$BUILD_DIR/main"

# Compiler and flags
CC="zig cc"
SRC_FILES="src/main.c"

# Compile the program
$CC $SRC_FILES -o $EXECUTABLE

# Check if compilation was successful
if [ $? -ne 0 ]; then
  echo "Compilation failed."
  exit 1
fi

# Function to generate the configuration from the filename
generate_config() {
  local file=$1
  local config_file=$2

  # Extract information from the filename
  local base=$(basename "$file")
  local name=$(echo $base | cut -d'.' -f2)
  # local name=$base

  # name = $(echo $name | cut -d'/' -f2)
  
  # chceck if the file name contains + or -
  if [[ $name == *"+"* ]]; then
  	local perfect_sequence=$(echo $name | cut -d'+' -f1)
  	local positive_errors=$(echo $name | cut -d'+' -f2 )
  else
  	local perfect_sequence=$(echo $name | cut -d'-' -f1)
  	local negative_errors=$(echo $name | cut -d'-' -f2 )
  fi

  # Default values if not present
  [ -z "$negative_errors" ] && negative_errors=0
  [ -z "$positive_errors" ] && positive_errors=0

  # Calculate data size
  local data_size
  if [ "$negative_errors" -ne 0 ]; then
    data_size=$((perfect_sequence - negative_errors))
  else
    data_size=$((perfect_sequence + positive_errors))
  fi

  # Create the configuration file
  cat <<EOF > "$config_file"
#define PERFECT_SEQUENCE $perfect_sequence
#define NEGATIVE_ERRORS $negative_errors
#define POSITIVE_ERRORS $positive_errors
#define DATA_SIZE $data_size
#define FILE_SOURCE "../$file"

#define CHAIN 10
#define POPULATION_SIZE 100
#define GENERATIONS 1000
#define ELITE_SIZE 10
#define MUTATION_RATE 0.1
#define DEBUG 0

#define SEQ_A 0
#define SEQ_C 1
#define SEQ_G 2
#define SEQ_T 3
#define SEQ_SIZE 2

#define STRING_SIZE 100
#define NON_SEQ_LETTER 1
EOF
}

# Populate the array with files from the specified directory
FILES=($(ls $DIR/*))

# empty the results file
echo "" > "results.txt"

# Iterate over each file in the array and run the program
for FILE in "${FILES[@]}"; do
  CONFIG_FILE="lib/globals.h"
  # echo $FILE>>"results.txt"
  
  # Generate the configuration file
  generate_config "$FILE" "$CONFIG_FILE"
  
  echo "Running program with input file: $FILE"
  # (cd $BUILD_DIR && time ./main 2>> "results.txt" ) 2>>"results.txt"
  (cd $BUILD_DIR && time ./main)

  # echo "" >> "results.txt"

done

# remove user and sys time
# sed -i 's/user.*//g' "results.txt"
# sed -i 's/sys.*//g' "results.txt"



# Populate the array with files from the specified directory
# FILES=($(ls $DIR/*))
#
# # Iterate over each file in the array and run the program
# for FILE in "${FILES[@]}"; do
#   echo "Running program with input file: $FILE"
#   (cd $BUILD_DIR && time ./main "$FILE")
# done
