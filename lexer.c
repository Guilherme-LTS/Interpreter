#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./hash.h"

#define MAX_LENGTH 100 // Define um valor máximo para o comprimento dos identificadores

// Define uma estrutura para as variáveis
struct variable
{
    char name[MAX_LENGTH]; // Nome da variável
    int value;             // Valor da variável
    UT_hash_handle hh;     // Campo especial para uso da biblioteca hash
};

struct variable *variables = NULL; // Cria uma variável global para armazenar todas as variáveis

// Função para inserir ou atualizar uma variável na tabela hash
void insert_variable(char *name, int value)
{
    struct variable *var;

    HASH_FIND_STR(variables, name, var); // Procura pela variável na tabela hash
    if (var == NULL)
    { // Se a variável não foi encontrada, cria uma nova
        var = malloc(sizeof(struct variable));
        strcpy(var->name, name);
        var->value = value;
        HASH_ADD_STR(variables, name, var);
    }
    else
    { // Se a variável já existia, atualiza o valor
        var->value = value;
    }
}

// Função para imprimir todas as variáveis presentes na tabela hash
void print_variables()
{
    struct variable *var;

    printf("Variables:\n");
    for (var = variables; var != NULL; var = var->hh.next)
    { // Percorre todas as variáveis da tabela
        printf("%s = %d\n", var->name, var->value);
    }
}

// Função para liberar a memória utilizada pelas variáveis
void free_variables()
{
    struct variable *var, *tmp;

    HASH_ITER(hh, variables, var, tmp)
    {                             // Percorre todas as variáveis da tabela
        HASH_DEL(variables, var); // Remove a variável da tabela
        free(var);                // Libera a memória utilizada pela variável
    }
}

// Definição das constantes de tokens
#define IDENTIFIER 1
#define INTEGER 2
#define ASSIGN 3
#define LPAREN 4
#define RPAREN 5
#define SEMICOLON 6
#define ADD 7
#define EXPRESSION 8

// Definição das variáveis globais para uso do analisador léxico
int yylex();
extern FILE *yyin;
void yyerror(char *s);

// Função principal
int main(int argc, char *argv[])
{
    int token;
    yyin = fopen("input.txt", "r"); // Abre o arquivo de entrada
    while ((token = yylex()))
    { // Lê e processa todos os tokens até o final do arquivo
        switch (token)
        {
        case IDENTIFIER:
            insert_variable(yytext, 0); // Insere o identificador na tabela hash
            printf("IDENTIFIER: %s\n", yytext);
            break;
        case INTEGER:
            insert_variable(yytext, atoi(yytext)); // Insere o valor inteiro na tabela hash
            printf("INTEGER: %s\n", yytext);
            break;
        case ASSIGN:
            printf("ASSIGN\n");
            break;
        case LPAREN:
            printf("LPAREN\n");
            break;
        case RPAREN:
            printf("RPAREN\n");
            break;
        case SEMICOLON:
            printf("SEMICOLON\n");
            break;
        case ADD:
            printf("ADD\n");
            break;
        case EXPRESSION:
            printf("EXPRESSION\n");
            break;
        default:
            yyerror("Invalid character");
            break;
        }
    }
    print_variables(); // Imprime todas as variáveis presentes na tabela hash
    free_variables();  // Libera a memória utilizada pelas variáveis
    fclose(yyin);      // Fecha o arquivo de entrada
    return 0;
}

// Implementação da função de erro para o analisador sintático
void yyerror(char *s)
{
    printf("Error: %s\n", s);
}
