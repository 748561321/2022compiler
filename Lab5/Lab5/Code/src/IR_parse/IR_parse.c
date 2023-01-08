//
// Created by hby on 11/22/22.
//

#include <IR_parse.h>
#include <container/treap.h>

DEF_MAP(unsigned, IR_var)
DEF_MAP(unsigned, IR_label)
static Map_unsigned_IR_var IR_var_map;
static Map_unsigned_IR_label IR_label_map;

#ifndef PARSE_CMM
int yylex() {
    return IR_yylex();
}
#endif

static FILE *open_tmp(FILE *file) {
    size_t len = 0;
    static char buffer[BUFSIZ] = {'\0'};
    FILE *tmp = tmpfile();
    // origin
    while ((len = fread(buffer, sizeof(char), BUFSIZ, file)) > 0)
        fwrite(buffer, sizeof(char), len, tmp);
    // append
    static char *append_code = "\n\n";
    fwrite(append_code, sizeof(char), strlen(append_code), tmp);
    fclose(file);
    fseek(tmp, 0, SEEK_SET);
    return tmp;
}

void IR_parse(const char *input_IR_path) {
    Map_unsigned_IR_var_init(&IR_var_map);
    Map_unsigned_IR_label_init(&IR_label_map);
    FILE *in_ir_file = NULL;
    if(input_IR_path) {
        in_ir_file = fopen(input_IR_path, "r");
        if(!in_ir_file) {
            perror(input_IR_path);
            exit(1);
        }
#ifdef IR_IN_APPEND_EOL
        in_ir_file = open_tmp(in_ir_file);
#endif
        IR_yyrestart(in_ir_file);
    }
    IR_yyparse();
    if(in_ir_file) {
        fclose(in_ir_file);
    }
    Map_unsigned_IR_var_teardown(&IR_var_map);
    Map_unsigned_IR_label_teardown(&IR_label_map);
}

//// ================================== symbol gen ==================================

static unsigned hash_string(const char *s) {
    unsigned val = 0;
    for(; *s; s ++) val = val * 131 + *s;
    return val;
}

IR_var get_IR_var(const char *id) {
    unsigned id_hash = hash_string(id);
    if(Map_unsigned_IR_var_exist(&IR_var_map, id_hash))
        return Map_unsigned_IR_var_get(&IR_var_map, id_hash);
    else {
        IR_var var = ir_var_generator();
        Map_unsigned_IR_var_set(&IR_var_map, id_hash, var);
        return var;
    }
}

IR_label get_IR_label(const char *id) {
    unsigned id_hash = hash_string(id);
    if(Map_unsigned_IR_label_exist(&IR_label_map, id_hash))
        return Map_unsigned_IR_label_get(&IR_label_map, id_hash);
    else {
        IR_label label = ir_label_generator();
        Map_unsigned_IR_label_set(&IR_label_map, id_hash, label);
        return label;
    }
}