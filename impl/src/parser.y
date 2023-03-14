%code requires {

#include "ecc/ast.h"

ecc::ASTNode *parseFile(const char *fname);

extern int ecc_lineno;
extern int ecc_colno;

struct TokenInfo {
  int row;
  int col;
  char *literal;
};

}

%{

#include "ecc/ast.h"

int yylex(void);
void yyrestart(FILE *);
void yyerror(struct ParseContext *, const char *s);

struct ParseContext {
  ecc::ASTNode *root;
};

%}

%parse-param {struct ParseContext *p}
%define parse.lac full
%define parse.error verbose

%union {
struct TokenInfo tok;
ecc::ExprNode *expr;
}

%token<tok> INTIMM
%token<tok> IDENTIFIER
%token<tok> SLITERAL
%token      RETURN

%type<expr> expr

%%

program: function_or_class_declarations

function_or_class_declarations: function_or_class_declaration function_or_class_declarations
			      | function_or_class_declaration

function_or_class_declaration: function_declaration | class_declaration

function_declaration: IDENTIFIER IDENTIFIER '(' arg_list ')' compound_statement {
  printf("function declaration!\n");
}

compound_statement: '{' statements '}' {}

statements: statement statements
	  | statement

statement: function_call ';' {}
	 | RETURN expr ';' {}
	 | RETURN ';' {}

function_call: IDENTIFIER '(' param_list ')' {
  printf("calls %s\n", $1.literal);
}

arg_list: variable_decl ',' arg_list { }
	| variable_decl { }
	|

param_list: expr ',' param_list { }
	  | expr { }
	  |

expr: SLITERAL {
  $$ = new ecc::StringLiteral($1.row, $1.col, $1.literal);
}

variable_decl: IDENTIFIER IDENTIFIER { printf("%s %s\n", $1.literal, $2.literal); }

class_declaration: IDENTIFIER IDENTIFIER '{' '}' { }

%%

int ecc_colno = 1;
int ecc_lineno = 1;

ecc::ASTNode *parseFile(const char *fname) {
  FILE *fd = fopen(fname, "r");
  if (!fd) {
    return nullptr;
  }
  ParseContext pc;
  yyrestart(fd);
  yyparse(&pc);
  return pc.root;
}

void yyerror(struct ParseContext *, const char *s) {
  printf("Stuck at %d,%d: %s\n", ecc_lineno, ecc_colno, s);
}
