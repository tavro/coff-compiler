#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "global.h"

/* generates error messages */
int error(char *msg)
{
        fprintf(stderr, "line %d: %s\n", line_number, msg);
        return 1;
}

/* -------------------------- */
int insert(char s[], int tok);
int lookup(char s[]);
int lexical_analyzer() {
	int t;

	while(1) {
		t = getchar();
		if (t == ' ' || t == '\t');             /* strip white space */
		else if (t == '\n')
			line_number = line_number + 1; 	/* new line */
		else if (isdigit(t)) {                 	/* is digit */
			ungetc(t, stdin);
			scanf("%d", &token_value);
			return NUM;
		}
		else if (isalpha(t)) {			/* is letter */
			int p, buffer_index = 0;

			while(isalnum(t)) {		/* is alphanumeric */
				lex_buffer[buffer_index] = t;
				t = getchar();
				buffer_index = buffer_index + 1;

				if (buffer_index >= BUFFER_SIZE)
					error("compiler error: buffer index out of range");
			}

			lex_buffer[buffer_index] = EOS;
			if (t != EOF)
				ungetc(t, stdin);

			p = lookup(lex_buffer);
			if (p == 0)
				p = insert(lex_buffer, ID);

			token_value = p;
			return symbol_table[p].token;
		}
		else if (t == EOF)
			return DONE;
		else {
			token_value = NONE;
			return t;
		}
	}
}

/* -------------------------- */

/* generates output */
void emit(int t, int t_value)
{
        switch(t) {
                case '+': case '-': case '*': case '/':
                        printf("%c\n", t);
                        break;
                case DIV:
                        printf("DIV\n");
                        break;
                case MOD:
                        printf("MOD\n");
                        break;
                case NUM:
                        printf("%d\n", t_value);
                        break;
                case ID:
                        printf("%s\n", symbol_table[t_value].lexptr);
                        break;
                default:
                        printf("token %d, token_value %d\n", t, t_value);
        }
}

/* -------------------------- */

/* returns position of entry for s */
int lookup(char s[]) {
	int p;
	for(p = last_entry; p > 0; p = p - 1)
		if (strcmp(symbol_table[p].lexptr, s) == 0)
			return p;
	return 0;
}

/* returns position of entry for s */
int insert(char s[], int tok) {
	int len;
	len = strlen(s);

	if (last_entry + 1 >= SYM_MAX)
		error("compiler error: symbol table is full");

	if (last_char + len + 1 >= STR_MAX)
		error("compiler error: lexemes array is full");

	last_entry = last_entry + 1;
	symbol_table[last_entry].token = tok;
	symbol_table[last_entry].lexptr = &lexemes[last_char + 1];

	last_char = last_char + len + 1;
	strcpy(symbol_table[last_entry].lexptr, s);

	return last_entry;
}

/* -------------------------- */

struct entry keywords[] = {
        "div", DIV,
        "mod", MOD,
        0,     0
};

/* loads keywords into symbol table */
void init() {
        struct entry *p;
        for(p = keywords; p->token; p++)
                insert(p->lexptr, p->token);
}

/* -------------------------- */

void match(int t)
{
        if (lookahead == t)
                lookahead = lexical_analyzer();
        else error("compiler error: syntax error");
}

void expression();
void factor() {
        switch(lookahead) {
                case '(':
                        match('(');
                        expression();
                        match(')');
                        break;
                case NUM:
                        emit(NUM, token_value);
                        match(NUM);
                        break;
                case ID:
                        emit(ID, token_value);
                        match(ID);
                        break;
                default:
                        error("compiler error: syntax error");
        }
}

void term() {
        int t;

        factor();
        while(1) {
                switch(lookahead) {
                        case '*': case '/': case DIV: case MOD:
                                t = lookahead;
                                match(lookahead);
                                factor();
                                emit(t, NONE);
                                continue;
                        default:
                                return;
                }
        }
}

void expression() {
        int t;

        term();
        while(1) {
                switch(lookahead) {
                        case '+': case '-':
                                t = lookahead;
                                match(lookahead);
                                term();
                                emit(t, NONE);
                        default:
                                return;
                }
        }
}

/* parses & translates expression list */
void parse() {
        lookahead = lexical_analyzer();
        while(lookahead != DONE) {
                expression();
                match(';');
        }
}

/* -------------------------- */

int main() {
	init();
	parse();
	return 0;
}
