/* PROJECTNAME.h */
#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <errno.h>

#define ErrMem      0x01

typedef unsigned char int8;
typedef unsigned short int int16;
typedef unsigned int int32;
typedef unsigned long long int int64;

typedef int8 Args;

#define $1 (int8 *)
#define $2 (int16)
#define $4 (int32)
#define $8 (int64)
#define $c (char *)
#define $i (int)

typedef unsigned short int Reg;


struct s_registers{
    Reg ax;
    Reg bx;
    Reg cx;
    Reg dx;
    Reg sp;
    Reg ip;
};

typedef struct s_registers Registers;

struct s_cpu{
    Registers r;

};

typedef struct s_cpu CPU;

typedef int8 Stack[((unsigned int)(-1))];

enum e_opcode{
    mov = 0x01,
    nop = 0x02
};

typedef enum e_opcode Opcode; 

struct s_instruction{
    Opcode o;
    Args a[]; /* 0-2 bytes*/
};
typedef struct s_instruction Instruction;
typedef Instruction Program;

/*
    mov ax, 0x05 // (0x01 Or ax)
                0x01 -> mov instruction 
*/

struct s_vm{
    CPU c;
    Stack s;
    Program *p;
};
typedef struct s_vm VM;

struct s_instrmap{
    Opcode o;
    int8 size;
};

typedef struct s_instrmap IM;



static IM instrmap[] = {
    { mov, 0x03 },  // Opcode 'mov' with size 3
    { nop, 0x01 }   // Opcode 'nop' with size 1
};

VM *virtualmachine(Program*,int16);

void zero(int8 *str, int16 size) {
    int8 *p;
    int16 n;

    for (n=0, p=str; n<size; n++, p++)
        *p = 0;

    return;
}


void copy(int8 *dst, int8 *src, int16 size) {
    int8 *d, *s;
    int16 n;

    for (n=size, d=dst, s=src; n; n--, d++, s++)
        *d = *s;

    return;
}

Program* exampleprogram(void);

int main(int,char**);

