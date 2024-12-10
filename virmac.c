#include "virmac.h"

VM *virtualmachine(Program *pr, int16 progsz ){
    VM *p;
    Program* pp;
    int16 size;


    assert((pr) && (progsz));
    size = $2 sizeof(struct s_vm);

    p = (VM*) malloc($i size);
    
    if(!p){
        errno = ErrMem;
        return (VM*) 0;
    }

    zero($1 p, size);
    pp=(Program*)malloc($i progsz);
    if(!pp){
        free(p);
        errno = ErrMem;
        return(VM*)0;
    }
    copy($1 pp,$1 pr, progsz);
    return p;
}

Program* exampleprogram() {
    static Program prog[] = {
        {
            .o = mov,
            .a = { 0x00, 0x05 }
        },
        {
            .o = nop,
            .a = NoArgs
        }
    };
    return prog;
}

int8 map(Opcode o) {
    int8 n, ret = -1; // Default ret to -1 to handle no match
    IM *p;

    // Assuming IMs is defined as the size of instrmap
    for (n = IMs, p = instrmap; n; n--, p++) {
        if (p->o == o) {
            ret = p->size;
            break;
        }
    }

    return ret;
}


int main(int argc, char *argv[]) {
    Program *prog; 
    VM *vm;
    int16 prog_size;

    // Get the example program
    prog = exampleprogram();

    // Calculate the program size in bytes
    prog_size = sizeof(Instruction) * 2; // Two instructions in the example program

    // Print the address of the program (debugging)
    printf("Program address: %p\n", (void *)prog);

    // Create the virtual machine with the example program
    vm = virtualmachine(prog, prog_size);
    if (!vm) {
        fprintf(stderr, "Failed to initialize the virtual machine. Error: %d\n", errno);
        return EXIT_FAILURE;
    }

    // Print the VM's memory address (debugging)
    printf("Virtual Machine initialized at: %p\n", (void *)vm);

    // Clean up memory (in real use cases, you'd likely run the VM first)
    free(vm->p); // Free the copied program
    free(vm);    // Free the VM itself

    return EXIT_SUCCESS;
}
