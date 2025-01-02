#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int sys_t;

typedef enum
{
    PROCESSOR_OPCODE_NOP,
    PROCESSOR_OPCODE_MOV,
    PROCESSOR_OPCODE_CMP,
    PROCESSOR_OPCODE_JMP,
    PROCESSOR_OPCODE_JE,
    PROCESSOR_OPCODE_JL,
    PROCESSOR_OPCODE_JG,
    PROCESSOR_OPCODE_JLE,
    PROCESSOR_OPCODE_JGE,
    PROCESSOR_OPCODE_ADD,
    PROCESSOR_OPCODE_SUB,
    PROCESSOR_OPCODE_MUL,
    PROCESSOR_OPCODE_DIV,
    PROCESSOR_OPCODE_SQRT,
    PROCESSOR_OPCODE_PUSH,
    PROCESSOR_OPCODE_POP,
    PROCESSOR_OPCODE_LBL,
    PROCESSOR_OPCODE_CALL,
    PROCESSOR_OPCODE_RET,
    PROCESSOR_OPCODE_PRINT,
    PROCESSOR_OPCODE_INT,
    _PROCESSOR_OPCODE_NUM
} opcode_t;

typedef struct
{
    opcode_t opcode;
    sys_t args[2];
    size_t args_count;
} bin_instruction_t;

typedef struct
{
    bin_instruction_t* instructions;
    size_t count;
} bin_code_t;

typedef struct
{
    sys_t ic;
    sys_t flags;
    size_t r_size;
    sys_t* r;
} core_t;

typedef struct
{
    size_t ram_size;
    sys_t* ram;
} shared_memory_t;

typedef struct
{
    core_t* cores;
    shared_memory_t memory;
} cpu_t;

typedef struct
{
    size_t ram_size;
    size_t r_size;
} cpu_conf_t;

static const char* instruction_str[_PROCESSOR_OPCODE_NUM] =
{
    [PROCESSOR_OPCODE_NOP]   = "nop",
    [PROCESSOR_OPCODE_MOV]   = "mov",
    [PROCESSOR_OPCODE_CMP]   = "cmp",
    [PROCESSOR_OPCODE_JMP]   = "jmp",
    [PROCESSOR_OPCODE_JE]    = "je",
    [PROCESSOR_OPCODE_JL]    = "jl",
    [PROCESSOR_OPCODE_JG]    = "jg",
    [PROCESSOR_OPCODE_JLE]   = "jle",
    [PROCESSOR_OPCODE_JGE]   = "jge",
    [PROCESSOR_OPCODE_ADD]   = "add",
    [PROCESSOR_OPCODE_SUB]   = "sub",
    [PROCESSOR_OPCODE_MUL]   = "mul",
    [PROCESSOR_OPCODE_DIV]   = "div",
    [PROCESSOR_OPCODE_SQRT]  = "sqrt",
    [PROCESSOR_OPCODE_PUSH]  = "push",
    [PROCESSOR_OPCODE_POP]   = "pop",
    [PROCESSOR_OPCODE_LBL]   = NULL,
    [PROCESSOR_OPCODE_CALL]  = "call",
    [PROCESSOR_OPCODE_RET]   = "ret",
    [PROCESSOR_OPCODE_PRINT] = "prt",
    [PROCESSOR_OPCODE_INT]   = "int",
};

typedef struct
{
    const char* name;
    size_t num_of_args;
} instruction_desc_t;

static instruction_desc_t instruction_map[] =
{
    [PROCESSOR_OPCODE_NOP]   = { "nop",  0 },
    [PROCESSOR_OPCODE_MOV]   = { "mov",  2 },
    [PROCESSOR_OPCODE_CMP]   = { "cmp",  2 },
    [PROCESSOR_OPCODE_JMP]   = { "jmp",  1 },
    [PROCESSOR_OPCODE_JE]    = { "je",   1 },
    [PROCESSOR_OPCODE_JL]    = { "jl",   1 },
    [PROCESSOR_OPCODE_JG]    = { "jg",   1 },
    [PROCESSOR_OPCODE_JLE]   = { "jle",  1 },
    [PROCESSOR_OPCODE_JGE]   = { "jge",  1 },
    [PROCESSOR_OPCODE_ADD]   = { "add",  2 },
    [PROCESSOR_OPCODE_SUB]   = { "sub",  2 },
    [PROCESSOR_OPCODE_MUL]   = { "mul",  2 },
    [PROCESSOR_OPCODE_DIV]   = { "div",  2 },
    [PROCESSOR_OPCODE_SQRT]  = { "sqrt", 1 },
    [PROCESSOR_OPCODE_PUSH]  = { "push", 1 },
    [PROCESSOR_OPCODE_POP]   = { "pop",  1 },
    [PROCESSOR_OPCODE_PRINT] = { "prt",  1 },
    [PROCESSOR_OPCODE_INT]   = { "int",  1 },
};

static void init_stack(core_t* core)
{
    /* Stack init stub */
}

static void push_stack(core_t* core, sys_t value)
{
    /* Push stub */
}

static sys_t pop_stack(core_t* core)
{
    /* Pop stub */
    return 0;
}

static void execute_instruction(core_t* core, shared_memory_t* mem, bin_instruction_t instr)
{
    switch(instr.opcode)
    {
        case PROCESSOR_OPCODE_NOP:
        {
            core->ic++;
        }
        break;

        case PROCESSOR_OPCODE_MOV:
        {
            core->r[instr.args[0]] = core->r[instr.args[1]];
            core->ic++;
        }
        break;

        case PROCESSOR_OPCODE_CMP:
        {
            sys_t lhs = core->r[instr.args[0]];
            sys_t rhs = core->r[instr.args[1]];
            if (lhs == rhs) core->flags = 0; 
            else if (lhs < rhs) core->flags = -1; 
            else core->flags = 1;
            core->ic++;
        }
        break;

        case PROCESSOR_OPCODE_JMP:
        {
            core->ic = instr.args[0];
        }
        break;

        case PROCESSOR_OPCODE_JE:
        {
            if (core->flags == 0) core->ic = instr.args[0];
            else core->ic++;
        }
        break;

        case PROCESSOR_OPCODE_JL:
        {
            if (core->flags < 0) core->ic = instr.args[0];
            else core->ic++;
        }
        break;

        case PROCESSOR_OPCODE_JG:
        {
            if (core->flags > 0) core->ic = instr.args[0];
            else core->ic++;
        }
        break;

        case PROCESSOR_OPCODE_JLE:
        {
            if (core->flags <= 0) core->ic = instr.args[0];
            else core->ic++;
        }
        break;

        case PROCESSOR_OPCODE_JGE:
        {
            if (core->flags >= 0) core->ic = instr.args[0];
            else core->ic++;
        }
        break;

        case PROCESSOR_OPCODE_ADD:
        {
            core->r[instr.args[0]] += core->r[instr.args[1]];
            core->ic++;
        }
        break;

        case PROCESSOR_OPCODE_SUB:
        {
            core->r[instr.args[0]] -= core->r[instr.args[1]];
            core->ic++;
        }
        break;

        case PROCESSOR_OPCODE_MUL:
        {
            core->r[instr.args[0]] *= core->r[instr.args[1]];
            core->ic++;
        }
        break;

        case PROCESSOR_OPCODE_DIV:
        {
            if (core->r[instr.args[1]] != 0)
            {
                core->r[instr.args[0]] /= core->r[instr.args[1]];
            }
            core->ic++;
        }
        break;

        case PROCESSOR_OPCODE_SQRT:
        {
            if (core->r[instr.args[0]] >= 0)
            {
                /* integer sqrt stub */
                sys_t val = core->r[instr.args[0]];
                sys_t result = 0;
                while(result * result <= val) result++;
                core->r[instr.args[0]] = result - 1;
            }
            core->ic++;
        }
        break;

        case PROCESSOR_OPCODE_PUSH:
        {
            push_stack(core, core->r[instr.args[0]]);
            core->ic++;
        }
        break;

        case PROCESSOR_OPCODE_POP:
        {
            core->r[instr.args[0]] = pop_stack(core);
            core->ic++;
        }
        break;

        case PROCESSOR_OPCODE_LBL:
        {
            core->ic++;
        }
        break;

        case PROCESSOR_OPCODE_CALL:
        {
            push_stack(core, core->ic + 1);
            core->ic = instr.args[0];
        }
        break;

        case PROCESSOR_OPCODE_RET:
        {
            core->ic = pop_stack(core);
        }
        break;

        case PROCESSOR_OPCODE_PRINT:
        {
            printf("%d\n", core->r[instr.args[0]]);
            core->ic++;
        }
        break;

        case PROCESSOR_OPCODE_INT:
        {
            /* Interrupt stub */
            core->ic++;
        }
        break;

        default:
        {
            core->ic++;
        }
        break;
    }
}

cpu_t* cpu_create(const cpu_conf_t configuration)
{
    cpu_t* cpu = calloc(1, sizeof(cpu_t));
    cpu->cores = calloc(1, sizeof(core_t));
    cpu->cores->ic = 0;
    cpu->cores->flags = 0;
    cpu->cores->r_size = configuration.r_size;
    cpu->cores->r = calloc(configuration.r_size, sizeof(sys_t));
    init_stack(cpu->cores);

    cpu->memory.ram_size = configuration.ram_size;
    cpu->memory.ram = calloc(configuration.ram_size, sizeof(sys_t));

    return cpu;
}

void cpu_execute(cpu_t* cpu, bin_code_t code)
{
    core_t* core = &cpu->cores[0];
    while (core->ic < (sys_t)code.count)
    {
        bin_instruction_t instr = code.instructions[core->ic];
        execute_instruction(core, &cpu->memory, instr);
    }
}

const char* cpu_dump(cpu_t* cpu)
{
    static char buffer[1024];
    core_t* core = &cpu->cores[0];

    memset(buffer, 0, sizeof(buffer));

    sprintf(buffer + strlen(buffer), "ic=%d flags=%d\n", core->ic, core->flags);
    for (size_t i = 0; i < core->r_size; i++)
    {
        sprintf(buffer + strlen(buffer), "r%zu=%d ", i, core->r[i]);
    }
    sprintf(buffer + strlen(buffer), "\nmem: ");
    for (size_t j = 0; j < cpu->memory.ram_size; j++)
    {
        sprintf(buffer + strlen(buffer), "[%zu]=%d ", j, cpu->memory.ram[j]);
    }

    return buffer;
}

void cpu_destroy(cpu_t* cpu)
{
    free(cpu->cores->r);
    free(cpu->cores);
    free(cpu->memory.ram);
    free(cpu);
}

char* disassemble_instruction(bin_instruction_t instr)
{
    static char line[64];
    memset(line, 0, sizeof(line));
    const char* name = instruction_str[instr.opcode];
    if (!name)
    {
        sprintf(line, "lbl ");
        return line;
    }

    if (instr.args_count == 0)
    {
        sprintf(line, "%s", name);
    }
    else if (instr.args_count == 1)
    {
        sprintf(line, "%s %d", name, instr.args[0]);
    }
    else
    {
        sprintf(line, "%s %d, %d", name, instr.args[0], instr.args[1]);
    }
    return line;
}

char* cpu_disassemble(bin_code_t code)
{
    static char text[1024];
    memset(text, 0, sizeof(text));
    for (size_t i = 0; i < code.count; i++)
    {
        char* line = disassemble_instruction(code.instructions[i]);
        sprintf(text + strlen(text), "%s\n", line);
    }
    return text;
}

bin_code_t cpu_assemble(const char* asm_text)
{
    bin_code_t result;
    result.count = 0;
    result.instructions = NULL;

    /* Naive parser stub */
    /* Example: "mov 0, 1\nadd 0, 2\nret\n" */

    char* text_copy = strdup(asm_text);
    char* line = strtok(text_copy, "\n");
    while (line)
    {
        char* opcode_part = strtok(line, " \t");
        if (!opcode_part)
        {
            line = strtok(NULL, "\n");
            continue;
        }

        opcode_t op = _PROCESSOR_OPCODE_NUM;
        for (int i = 0; i < _PROCESSOR_OPCODE_NUM; i++)
        {
            const char* n = instruction_str[i];
            if (n && strcmp(opcode_part, n) == 0)
            {
                op = i;
                break;
            }
        }

        if (op == _PROCESSOR_OPCODE_NUM && strcmp(opcode_part, "lbl") == 0)
        {
            op = PROCESSOR_OPCODE_LBL;
        }

        bin_instruction_t instr;
        instr.opcode = op;
        instr.args[0] = 0;
        instr.args[1] = 0;
        instr.args_count = 0;

        if (op < _PROCESSOR_OPCODE_NUM)
        {
            size_t n_args = instruction_map[op].num_of_args;
            if (n_args > 0)
            {
                char* args_part = strtok(NULL, "");
                if (args_part)
                {
                    char* tok = strtok(args_part, ",");
                    size_t idx = 0;
                    while (tok && idx < n_args)
                    {
                        while (*tok == ' ') tok++;
                        instr.args[idx++] = atoi(tok);
                        tok = strtok(NULL, ",");
                    }
                    instr.args_count = n_args;
                }
            }
        }

        result.instructions = realloc(result.instructions,
                                       (result.count + 1) * sizeof(bin_instruction_t));
        result.instructions[result.count++] = instr;

        line = strtok(NULL, "\n");
    }

    free(text_copy);
    return result;
}
