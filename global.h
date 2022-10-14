#define BUFFER_SIZE 128
#define NONE        -1
#define EOS         '\0'

#define NUM         256
#define DIV         257
#define MOD         258
#define ID          259
#define DONE        260

#define DEF	    266
#define END         267

#define STR_MAX 999     /* size of lexeme array */
#define SYM_MAX 100     /* size of symbol table */

char lexemes[STR_MAX];
char lex_buffer[BUFFER_SIZE];

int  last_char = -1;    /* last position in lexemes */
int  last_entry = 0;    /* last used position in symbol table */

int token_value = NONE;
int line_number = 1;

int lookahead;

/* form of symbol table entry */
struct entry {
        char *lexptr;
        int  token;
};
struct entry symbol_table[SYM_MAX];
