#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

typedef struct 
{
    const char *mnemonic;
    uint8_t opcode;
} InstructionDef;

typedef struct 
{
    const char *name;
    uint8_t id;
} RegisterDef;


static const InstructionDef instructions[] =
{
    { "LD", 0x10 }
};

static const RegisterDef registers[] =
{
    { "R0", 0x00 },
    { "R1", 0x01 },
    { "R2", 0x02 },
    { "R3", 0x03 },
    { "R4", 0x04 },
    { "R5", 0x05 }
};

InstructionDef* getInstruction(char line[])
{
    char* token = strtok(line, " ");

    if (token == NULL)
    {
        return NULL;
    }

    for (size_t i = 0; i < sizeof(instructions) / sizeof(instructions[0]); i++)
    {
        if(strcmp(instructions[i].mnemonic, token) == 0)
        {
            printf("got instruction: %s\n", instructions[i].mnemonic);

            return &instructions[i];
        }
    }
}

int main()
{
    FILE* file = fopen("../tests/main.asm", "r");

    char line[128];

    if (file == NULL)
    {
        fprintf(stderr, "No such file exists.\n");

        return 1;
    }

    FILE* outputFile = fopen("../output/main.bin", "w");

    if (outputFile == NULL)
    {
        fprintf(stderr, "Couldn't create binary file.");

        return 1;
    }

    while(fgets(line, sizeof(line), file))
    {
        if (line[0] == "") continue;

        InstructionDef* instruction = getInstruction(line);

        if (instruction == NULL)
        {
            fprintf(stderr, "Failed to tokenize line.");

            return 1;
        }

        fwrite(&instruction->opcode, sizeof(instruction->opcode), 1, outputFile);
    }

    fclose(file);
    fclose(outputFile);

    return 0;
}