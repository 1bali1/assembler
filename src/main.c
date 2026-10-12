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

int main()
{
    FILE* file = fopen("../tests/main.asm", "r");

    char line[128];

    if (file == NULL)
    {
        fprintf(stderr, "No such file exists\n");

        return 1;
    }

    while(fgets(line, sizeof(line), file))
    {
        printf("%s", line);
    }

    fclose(file);

    return 0;
}