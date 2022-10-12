#include <math.h>

/* generates output */
void emit(int t, int t_value)
{
	FILE *fptr;                      // file var
	fptr = fopen("output.txt", "a"); // open file in write mode

        switch(t) {
                case '+': case '-': case '*': case '/':
			printf("%c\n", t);
			putc(t, fptr);
                        break;
                case DIV:
                        printf("DIV\n");
			fputs("DIV", fptr);
                        break;
                case MOD:
                        printf("MOD\n");
			fputs("MOD", fptr);
                        break;
                case NUM:
                        printf("%d\n", t_value);
			char str[99];
			sprintf(str, "%d", t_value);
			fputs(str, fptr);
                        break;
                case ID:
                        printf("%s\n", symbol_table[t_value].lexptr);
			fputs(symbol_table[t_value].lexptr, fptr);
                        break;
                default:
                        printf("token %d, token_value %d\n", t, t_value);
        }

	putc('\n', fptr); // write character to file
	fclose(fptr);     // close file
}
