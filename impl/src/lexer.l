%{

#include "./parser.tab.hh"
#define UPDATE_TOK               \
  do {                           \
    yylval.tok.literal = yytext; \
    yylval.tok.row = ecc_lineno; \
    yylval.tok.col = ecc_colno;  \
    ecc_colno += strlen(yytext); \
  } while(false)

%}

%option noyywrap

DIGITAL [0-9]
ID_START [a-zA-Z_]
ID_REST [a-zA-Z0-9_]
PRINTABLE [ -~\\"\\'\\\\\\n]
SPACE [ \t]

%%

"return" {
  UPDATE_TOK;
  return RETURN;
}

{SPACE}+ {
  ecc_colno += strlen(yytext);
}

\n {
  ++ecc_lineno;
  ecc_colno = 1;
}

{ID_START}{ID_REST}* {
  UPDATE_TOK;
  return IDENTIFIER;
}

{DIGITAL}{DIGITAL}* {
  UPDATE_TOK;
  ecc_colno += strlen(yytext);
  return INTIMM;
}

-{DIGITAL}{DIGITAL}* {
  UPDATE_TOK;
  return INTIMM;
}

("{") {
  UPDATE_TOK;
  return '{';
}

("}") {
  UPDATE_TOK;
  return '}';
}

"(" {
  UPDATE_TOK;
  return '(';
}

")" {
  UPDATE_TOK;
  ecc_colno += strlen(yytext);
  return ')';
}

";" {
  UPDATE_TOK;
  return ';';
}

\"{PRINTABLE}*\"     {
  UPDATE_TOK;
  return SLITERAL;
}

