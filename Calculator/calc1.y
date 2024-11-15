%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
int yyerror(char *s);
%}

%token NUMBER

%left '+' '-'
%left '*' '/'
%right UMINUS /* Unary minus */

%%

input:
    | input line
;

line:
    expr '\n' { printf("Result: %d\n", $1); }
;

expr:
    expr '+' expr { $$ = $1 + $3; }
  | expr '-' expr { $$ = $1 - $3; }
  | expr '*' expr { $$ = $1 * $3; }
  | expr '/' expr { 
        if ($3 == 0) {
            printf("Error: Division by zero\n");
            exit(1);
        }
        $$ = $1 / $3; 
    }
  | '-' expr %prec UMINUS { $$ = -$2; }
  | NUMBER { $$ = $1; }
;

%%

int main() {
    printf("Enter expressions to calculate (Ctrl+D to exit):\n");
    yyparse();
    return 0;
}

int yyerror(char *s) {
    fprintf(stderr, "Error: %s\n", s);
    return 0;
}

