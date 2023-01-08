#include <time.h>
#include <config.h>
#include <IR_parse.h>
#include <IR_optimize.h>

int main(int argc, char *argv[]) {
    srand(time(NULL));
    IR_parse(argc >= 2 ? argv[1] : NULL);
    IR_optimize();
    IR_output(argc >= 3 ? argv[2] : NULL);
    if(ir_program_global != NULL)
        RDELETE(IR_program, ir_program_global);
    return 0;
}
