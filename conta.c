% option yylineno % option noyywrap %
{
#include <stdio.h>
  void yyerror(char *s);
  %
}

% %

    "int"
{
  printf("Tipo: INT\n");
}
[a - zA - Z] + { printf("Identificador: %s\n", yytext); }
[0 - 9] + { printf("Valor: %s\n", yytext); }
"=" { printf("Operador de atribuição\n"); }
"(" { printf("Abre parênteses\n"); }
")" { printf("Fecha parênteses\n"); }
";" { printf("Fim de linha\n"); }
"+" { printf("Operador de adição\n"); }
[a - zA - Z] + [] *[+][] * [a - zA - Z] + { printf("Expressão: %s\n", yytext); }
. { yyerror("Caractere inválido"); }

% %

    void yyerror(char *s)
{
  printf("Erro: %s\n", s);
}

int main(int argc, char *argv[])
{
  yyin = fopen("conta.txt", "r");
  yylex();
  fclose(yyin);
  return 0;
}
