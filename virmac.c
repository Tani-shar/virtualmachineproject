#include "virmac.h"

VM *virtualmachine(Program *pr, int16 progsz ){
    VM *p;
    Program* pp;
    int16 size;


    assert((pr) && (progsz));
    size = $2 .sizeof(struct s_vm);

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
    copy(pp, pr, progsz);
    return p;
}

Program* exampleprogram(){
    static Program prog[] = {
        {
            .o = mov,
            .a = {
                0x00, 0x05
            }
        },
        {
            .o = nop,
            .a = NoArgs;
        }
    };

    return prog;

    
}

int main(int argc, char *argv[]){
    Program *prog; 
    VM* vm;

    prog = exampleprogram();
    vm = virtualmachine()
}