#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

typedef int64_t sys_t;


typedef enum {
    STACK_OK,
    STACK_ERROR_INIT,
    STACK_ERROR_OVERFLOW,
    STACK_ERROR_UNDERFLOW,
    STACK_ERROR_POP_DEST,
} stack_error_t;

typedef struct {
    sys_t* content;
    struct {
        size_t capacity;
        size_t used;
    } data;
} stack_t;

stack_t* stack_create(size_t num_of_elements) {
    if (num_of_elements == 0UL) {
        return NULL;

    }
    stack_t* new_stack = calloc(1, sizeof(stack_t));
    sys_t* new_capacity = calloc(num_of_elements, sizeof(sys_t));

    if (!new_stack)
        return NULL;
    if (!new_capacity){
        free(new_stack);
        return NULL;
    }

    new_stack->content = new_capacity;
    new_stack->data.capacity = num_of_elements;
    new_stack->data.used = 0UL;

    return new_stack;
}

stack_error_t stack_push(stack_t* stack, sys_t new_element) {
    if (stack == NULL || stack->content == NULL) {
        return STACK_ERROR_INIT;
    }
    if (stack->data.used >= stack->data.capacity)
        return STACK_ERROR_OVERFLOW;
    stack->content[stack->data.used++] = new_element;
    return STACK_OK;
}

stack_error_t stack_pop(stack_t* stack, sys_t* popped_element) {
    if (stack == NULL || stack->content == NULL) {
        return STACK_ERROR_INIT;
    }
    if (stack->data.used == 0UL)
        return STACK_ERROR_UNDERFLOW;

    if (popped_element == NULL)
        return STACK_ERROR_POP_DEST;

    (*popped_element) = stack->content[--stack->data.used];
    return 0;
}

void stack_destroy(stack_t* stack) {
    if (stack == NULL)
        return;

    if (stack->content != NULL)
        free(stack->content);

    free(stack);
}

// ---------------------------------------


const char* text = 
"; Это мой лучший код на свете."
"ldi R0, 1231341"
"mov R1, R0"
"add R0, R1"
"prt R0"
"int 0";

typedef struct {
    size_t ic;
    sys_t* R;
    stack_t* stack;
} core_t;

typedef struct {
    core_t* cores;
    size_t num_of_cores;
} cpu_t;

typedef struct {
    size_t num_of_cores;
    struct {
        size_t num_of_registers;
        size_t size_of_stack;
    } cores;
    struct {
        size_t size_of_ram;
    } ram;
} cpu_conf_t;

cpu_t* cpu_create(cpu_conf_t conf) {
    
    core_t* cores = calloc(conf.num_of_cores, sizeof(core_t));
    if (!cores)
        return NULL;

    for (size_t i = 0; i < conf.num_of_cores; ++i) {
        
    }
}


int main(void) {

}