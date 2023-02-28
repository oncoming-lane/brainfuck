#include<stdio.h>
#include<string.h>
#include <unistd.h>

#define MAX_TAPE 1024

int tape[MAX_TAPE] = {0};
unsigned int head = 0;

size_t progsz;

const char* prog;

int interp(int);
void print_tape(int ptr);


int skip(int ptr) {
    switch(prog[ptr]) {
        case '[': return skip(skip(ptr+1));
        case ']': return ptr+1;
        case  0 : printf("Error while skipping\n"); return -1;
        default : break;
    }
    return skip(ptr+1);
}


int cycle(int ptr) {
    if (tape[head]) {
        if (interp(ptr+1) == 1) 
            return cycle(ptr);
        else {
            printf("Bracket is not closed\n");
            return -1;
        }
    }
    else 
        return skip(ptr+1);
}

int test_interp(int a, int b){
    int c = a + b;
    
    if ( interp(0) != 0 ) 
        printf("Error while interpreting (closing of non-opened bracket)\n");
    
    if (interp(0) != c)
        printf("ERROR");
    else
        printf("%d", c);
}

int interp(int ptr) {
    if ( ptr >= progsz )
        return 0;
    if ( ptr < 0 ) return -1;
        print_tape(ptr);
    switch ( prog[ptr] ) {
        case '+': tape[head]++; break;
        case '-': tape[head]--; break;
        case '<': head--; break;
        case '>': head++; break;
        case '.': printf("Output at %d: %d\n", head, (tape[head])); break;
                  //  return (tape[head]); break;
        case ',': if (scanf("%d", &tape[head])!=1){ 
                    printf("Error: integer expected!\n");
                    return -2;
                  }
                  break;
        case '[': return interp(cycle(ptr)); 
        case ']': return 1;
        case   0: return 0;
        default : break;
    }
    return interp(ptr+1);
}


void print_tape(int ptr) {
    int i;
    
    printf("%c ", prog[ptr]);
    for( i = 0; i < 15; i++ )
        printf("%c%d ", (head == i) ? '>' : ' ',tape[i]);
    printf("\n");
    
}


int main() {  

    //addition
    prog = ",>,<[->>+<<]>[->+<]>.";
    /*
    
    // subtraction
    prog = ">,>,<[>>+<<-]>[>-<-]>.";

    // multiplication
    prog = ",>,<[->[->+>+<<]>>[-<<+>>]<<<]>[-]>."; 
    prog = ",>,<[->[>+>+<<-]>>[<<+>>-]<[->>+<<]<<]>>>>.";

    // division 
    prog = ",>,<>[->+>>+<<<]<[->+<]>[->>+<<<+>]>>[->>+<<]<[-<+>]>>[-<+<+>>]<[->+<]<[-<+>]>>[-<+<+>>]<[->+<]<<->>>>[->+<]->[->[>]++[-<+]->]<-->---.<+[-+++[---<+++]---<[->>+++[--->+++]---[+]-->[-<+>]---<+++[---<+++]---<]<<[->+>+<<]>[-<+>]>>>+++[--->+++]---<++]-+++[---<+++]---<[->>+++[--->+++]--->+<<+++[---<+++]---<].>>+++[--->+++]--->[-<<[++++[---<+++]---<<<<-+++[--->+++]--->+++[--->+++]---<]>[+]<--->>[-<+>]<]<<+++[---<+++]---<<<[->>+<<]<[->+<]>[->+<<+>]<[-<->>+<]>>>[-<<<+>>>]<<[-]>>>[+]<<<<[->>>+>+<<<<]>>>[-<<<+>>>]<<<<[>[-<->]>+>>>[-<+<<<+>>>>]<[->+<]<<<<]>>.>."; 
    
    //exponentiation 
    prog = ",>,<[->>+>+<<<]>>>[-<<<+>>>]+<<[->[->[->+>+<<]>>[-<<+>>]<<<]>[-]<<<[->>+>+<<<]>>>[-<<<+>>>]>[-<+>]<<<]>>";
    prog = ",>,[->>>+<<<]<[->+<]+>>>>[-<<<<[->[->+>+<<]>[-<+>]<<]>>>>[->>>+<<<]<<<[->>>+<<<]>>>>>>]<<<<.";
    
    */

    progsz = strlen(prog);
    if ( interp(0) != 0 ) {
        printf("Error while interpreting (closing of non-opened bracket)\n");
    }
    
}