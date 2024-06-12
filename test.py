import os
import time

GLOBALS_PATH = "./lib/globals.h"
TEST_FILES_PATH = "./res"
TEST_RES_PATH = "./test_results.csv"

fileNames = [f for f in os.listdir(TEST_FILES_PATH) if os.path.isfile(os.path.join(TEST_FILES_PATH, f))]

def editGlobals(perfect_sequence: int, negative_errors: int, positive_errors: int, data_size: int, fileName: str):
    with open(GLOBALS_PATH, 'r') as file:
        lines = file.readlines()
    with open(GLOBALS_PATH, 'w') as file:
        for line in lines:
            if line.startswith("#define PERFECT_SEQUENCE"):
                file.write(f"#define PERFECT_SEQUENCE {perfect_sequence}\n")
            elif line.startswith("#define NEGATIVE_ERRORS"):
                file.write(f"#define NEGATIVE_ERRORS {negative_errors}\n")
            elif line.startswith("#define POSITIVE_ERRORS"):
                file.write(f"#define POSITIVE_ERRORS {positive_errors}\n")
            elif line.startswith("#define DATA_SIZE"):
                file.write(f"#define DATA_SIZE {data_size}\n")
            elif line.startswith("#define FILE_SOURCE"):
                file.write(f"#define FILE_SOURCE \"../res/{fileName}\"\n")
            else:
                file.write(line)


def getDataFromFileName(fileName: str):
    data = fileName.split(".")[1]

    splitter = data.split("-")
    if len(splitter) > 1:
        perfect_sequence = int(splitter[0])
        negative_errors = int(splitter[1])
        positive_errors = 0
        data_size = perfect_sequence - negative_errors
        return perfect_sequence, negative_errors, positive_errors, data_size
    
    splitter = data.split("+")
    if len(splitter) > 1:
        perfect_sequence = int(splitter[0])
        negative_errors = 0
        positive_errors = int(splitter[1])
        data_size = perfect_sequence + positive_errors
        return perfect_sequence, negative_errors, positive_errors, data_size
    
    return 0, 0, 0, 0

def compileCProgram():
    os.system("make build -B")

def runCProgram() -> str:
    return os.popen("make run -B").read()

def writeResult(file_name: str, measured_time: float, programOutput: str):
    with open(TEST_RES_PATH, 'a') as res_file:
        res_file.write(f"{file_name},{measured_time},{programOutput}\n")


os.system("echo "" > test_results.csv")
for fileName in fileNames:
    perfect_sequence, negative_errors, positive_errors, data_size = getDataFromFileName(fileName)
    editGlobals(perfect_sequence, negative_errors, positive_errors, data_size, fileName)
    compileCProgram()

    start_time = time.time()
    programOutput = runCProgram()
    end_time = time.time()

    measured_time = end_time - start_time
    programOutput = programOutput[programOutput.find("\n")+1:]
    programOutput = programOutput.replace("\n", ",")
    writeResult(fileName, measured_time, programOutput)
    # break
