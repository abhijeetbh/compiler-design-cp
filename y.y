%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylex();
extern int line_no;
extern FILE* yyin;
FILE* out_fp;

void yyerror(const char *s);

struct Symbol {
    char name[50];
    int type;
    // 0 is int, 1 is float, 2 is void, and 3 is class object
    int scope;
    // 0 global, 1 class, 2 local
} sym_table[100];

int sym_count = 0;
int current_scope = 0;
int expected_return_type = -1;
int errors = 0;

void add_symbol(char* name, int type) {
    for (int i = 0; i < sym_count; i++) {
        if (strcmp(sym_table[i].name, name) == 0 && sym_table[i].scope == current_scope) {
            fprintf(out_fp, "Semantic Error at line %d: variable '%s' already declared in this scope\n", line_no, name);
            errors++;
            return;
        }
    }
    strcpy(sym_table[sym_count].name, name);
    sym_table[sym_count].type = type;
    sym_table[sym_count].scope = current_scope;
    sym_count++;
}

int get_symbol_type(char* name) {
    for (int i = sym_count - 1; i >= 0; i--) {
        if (strcmp(sym_table[i].name, name) == 0) {
            return sym_table[i].type;
        }
    }
    fprintf(out_fp, "Semantic Error at line %d: undeclared variable '%s'\n", line_no, name);
    errors++;
    return -1; 
}

void check_assignment(char* name, int rhs_type) {
    int lhs_type = get_symbol_type(name);
    if (lhs_type == 0 && rhs_type == 1) {
        fprintf(out_fp, "Semantic Error at line %d: cannot assign float value to int variable '%s'\n", line_no, name);
        errors++;
    }
}

void check_array_index(int idx_type) {
    if (idx_type == 1) {
        fprintf(out_fp, "Semantic Error at line %d: array index must be an integer\n", line_no);
        errors++;
    }
}

void check_return_type(int ret_type) {
    if (expected_return_type == 0 && ret_type == 1) {
        fprintf(out_fp, "Semantic Error at line %d: return type mismatch: function declared as 'int' but returns 'float'\n", line_no);
        errors++;
    }
}

void print_symbol_table() {
    fprintf(out_fp, "\n--- SYMBOL TABLE ---\n");
    fprintf(out_fp, "Name\t\tType\tScope\n");
    fprintf(out_fp, "--------------------------------\n");
    for (int i = 0; i < sym_count; i++) {
        char* type_str = (sym_table[i].type == 0) ? "int" : (sym_table[i].type == 1) ? "float" : "other";
        char* scope_str = (sym_table[i].scope == 0) ? "global" : (sym_table[i].scope == 1) ? "class" : "local";
        fprintf(out_fp, "%-15s %-7s %-7s\n", sym_table[i].name, type_str, scope_str);
    }
    fprintf(out_fp, "--------------------------------\n\n");
}
%}

%union {
    int type; 
    // 0 aahe int, 1 float
    char* str;
}

%token HEADER PREPROCESSOR CLASS INT FLOAT VOID IF ELSE FOR WHILE RETURN MAIN PRINTF
%token <type> INT_CONST FLOAT_CONST
%token <str> ID STRING_LITERAL
%token OP_ARITH OP_REL OP_ASSIGN

%type <type> Type Expression Term Factor MethodCall

%start Program

%%

Program: Elements ;

Elements: Element Elements | Element ;

Element: HEADER | PREPROCESSOR | ClassDef | FunctionDef | MainFunc ;

ClassDef: CLASS ID '{' { current_scope = 1; } ClassMembers '}' ';' { current_scope = 0; } ;

ClassMembers: ClassMember ClassMembers | ClassMember ;

ClassMember: Declaration | ConstructorDef | MethodDef ;

ConstructorDef: ID '(' Params ')' '{' Statements '}' ;

MethodDef: Type ID '(' Params ')' '{' { expected_return_type = $1; current_scope = 2; } Statements '}' { current_scope = 1; } ;

FunctionDef: Type ID '(' Params ')' '{' { expected_return_type = $1; current_scope = 2; } Statements '}' { current_scope = 0; } ;

MainFunc: INT MAIN '(' ')' '{' { expected_return_type = 0; current_scope = 2; } Statements '}' { current_scope = 0; } ;

Type: INT { $$ = 0; } | FLOAT { $$ = 1; } | VOID { $$ = 2; } ;

Params: ParamList | /* empty */ ;
ParamList: Param ',' ParamList | Param ;
Param: Type ID { add_symbol($2, $1); } ;

Statements: Statement Statements | Statement | /* empty */ ;

Statement: Declaration | Assignment | IfStmt | WhileStmt | ForStmt | PrintfStmt | ReturnStmt | MethodCallStmt | ScopeStmt ;

ScopeStmt: '{' Statements '}' ;

Declaration: Type ID ';' { add_symbol($2, $1); }
           | Type ID OP_ASSIGN Expression ';' { add_symbol($2, $1); check_assignment($2, $4); }
           | Type ID '[' ID ']' ';' { add_symbol($2, $1); } 
           | ID ID '(' Expression ',' Expression ')' ';' { add_symbol($2, 3); /* Class instance */ } ;

Assignment: ID OP_ASSIGN Expression ';' { check_assignment($1, $3); }
          | ID '[' ID ']' OP_ASSIGN Expression ';' { check_array_index(get_symbol_type($3)); }
          | ID '[' ID ']' OP_ASSIGN ID '[' ID ']' OP_ARITH ID ';' { check_array_index(get_symbol_type($3)); check_array_index(get_symbol_type($8)); } ;

IfStmt: IF '(' Expression ')' Statement ELSE Statement 
      | IF '(' Expression ')' Statement ;

WhileStmt: WHILE '(' Expression ')' Statement ;

ForStmt: FOR '(' ID OP_ASSIGN INT_CONST ';' ID OP_REL ID ';' ID OP_ARITH OP_ARITH ')' Statement ;

PrintfStmt: PRINTF '(' STRING_LITERAL ',' ID ')' ';' 
          | PRINTF '(' STRING_LITERAL ',' ID '[' ID ']' ')' ';' ;

ReturnStmt: RETURN Expression ';' { check_return_type($2); } ;

MethodCallStmt: ID '.' ID '(' ')' ';' 
              | Type ID OP_ASSIGN ID '.' ID '(' ')' ';' { add_symbol($2, $1); }
              | Type ID OP_ASSIGN ID '(' ID ',' INT_CONST ')' ';' { add_symbol($2, $1); } ;

Expression: Expression OP_ARITH Term { $$ = ($1 == 1 || $3 == 1) ? 1 : 0; }
          | Expression OP_REL Term { $$ = 0; }
          | Term { $$ = $1; } ;

Term: Factor { $$ = $1; } ;

Factor: ID { $$ = get_symbol_type($1); }
      | INT_CONST { $$ = 0; }
      | FLOAT_CONST { $$ = 1; }
      | ID '[' ID ']' { $$ = get_symbol_type($1); check_array_index(get_symbol_type($3)); }
      | MethodCall { $$ = $1; } ;

MethodCall: ID '(' ')' { $$ = 0; } ;

%%

void yyerror(const char *s) {}

int main() {
    out_fp = fopen("outputNoErrors.txt", "w");
    if (!out_fp) {
        printf("Error opening output file!\n");
        return 1;
    }
    
    fprintf(out_fp, "TOKENS\n");
    yyin = fopen("noErrors.txt", "r");
    yyparse();
    
    print_symbol_table();
    
    fprintf(out_fp, "\nERRORS\n");
    if (errors > 0) {
        fprintf(out_fp, "Errors: %d\n", errors);
        fprintf(out_fp, "Program not accepted.\n");
    } else {
        fprintf(out_fp, "Output: No error\n");
        fprintf(out_fp, "Code accepted\n");
    }
    
    fclose(out_fp);
    return 0;
}
