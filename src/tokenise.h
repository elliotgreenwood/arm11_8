#ifndef TOKENISE_H
#define TOKENISE_H

#include "helpers/definitions.h"
#include "helpers/symbolmap.h"

typedef enum {LABEL,LITERAL,EXPRESSION,OTHER,NEWLINE,ENDFILE} TokenType;

typedef struct {
  char *value;
  TokenType type;
} Token;

typedef struct {
  int size;
  int fullCapacity;
  Token *tokens;
} Tokens;

void tokens_init(Tokens *tokens);
void tokens_add(Tokens *tokens, char *value, TokenType type);
//Helpers
bool isLabel(char *string);
bool isLiteral(char *string);
bool isExpression(char *string);
void tokens_free(Tokens *tokens);

int mnemonic_name(Token *token);

#endif /* end of include guard: TOKENISE_H */
