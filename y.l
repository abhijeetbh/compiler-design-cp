%{
#include "y.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern FILE *out_fp;
int line_no = 1;

void print_token(const char* token_type, const char* lexeme) {
    if (out_fp) {
        fprintf(out_fp, "Line %d: %s %s\n", line_no, token_type, lexeme);
    }
}
%}

%option noyywrap

%%

"//".* { /* Single line comment [cite: 43] */ }
"/*"([^*]|\*+[^*/])*\*+"/" {
	for(int i=0; yytext[i]; i++) if(yytext[i] == '\n') line_no++;
    }

"#include"[ ]*"<"[^>]+">" { print_token("HEADER", yytext); return HEADER; }
"#define"[ ]+[A-Za-z_][A-Za-z0-9_]*[ ]+[0-9]+ { print_token("PREPROCESSOR", yytext); return PREPROCESSOR; }

"class"                 { print_token("KEYWORD", yytext); return CLASS; }
"int"                   { print_token("KEYWORD", yytext); yylval.type = 0; return INT; }
"float"                 { print_token("KEYWORD", yytext); yylval.type = 1; return FLOAT; }
"void"                  { print_token("KEYWORD", yytext); yylval.type = 2; return VOID; }
"if"                    { print_token("KEYWORD", yytext); return IF; }
"else"                  { print_token("KEYWORD", yytext); return ELSE; }
"for"                   { print_token("KEYWORD", yytext); return FOR; }
"while"                 { print_token("KEYWORD", yytext); return WHILE; }
"return"                { print_token("KEYWORD", yytext); return RETURN; }
"main"                  { print_token("MAIN", yytext); return MAIN; }
"printf"                { print_token("PREDEFINED FUNCTION", yytext); return PRINTF; }

[A-Za-z_][A-Za-z0-9_]* { print_token("IDENTIFIER", yytext); yylval.str = strdup(yytext); return ID; }
[0-9]+                  { print_token("INTEGER CONSTANT", yytext); yylval.type = 0; return INT_CONST; }
[0-9]+\.[0-9]+          { print_token("FLOAT CONSTANT", yytext); yylval.type = 1; return FLOAT_CONST; }
\"[^\"]*\"              { print_token("STRING LITERAL", yytext); return STRING_LITERAL; }

"+"|"-"|"*"|"/"         { print_token("OPERATOR", yytext); return OP_ARITH; }
"<"|">"|"<="|">="|"=="  { print_token("OPERATOR", yytext); return OP_REL; }
"="                     { print_token("OPERATOR", yytext); return OP_ASSIGN; }

"{"|"}"|"("|")"|"["|"]"|";"|","|"." { print_token("SPECIAL SYMBOL", yytext); return yytext[0]; }

[ \t\r]+                { }
\n                      { line_no++; }
.                       { }

%%
