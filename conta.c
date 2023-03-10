% {
#include <stdio.h>
      % }

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

% %

    int main(int argc, char *argv[])
{
  yyin = fopen("conta.txt", "r");
  yylex();
  fclose(yyin);
  return 0;
}
