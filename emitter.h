#include <math.h>

/* generates output */
void emit(int t, int t_value)
{
	FILE *fptr;                      // file var
	fptr = fopen("output.txt", "a"); // open file in write mode

        switch(t) {
                case '+': case '-': case '*': case '/':
			putc(t, fptr);
                        break;
                case DIV:
			fputs("DIV", fptr);
                        break;
                case MOD:
			fputs("MOD", fptr);
                        break;
                case NUM:
			char str[99];
			sprintf(str, "%d", t_value);
			fputs(str, fptr);
                        break;
		case DEF:
			//fputs("int main(int argc, char ** argv) {", fptr);
			break;
		case END:
			//fputs("}", fptr);
			break;
                case ID:
			fputs(symbol_table[t_value].lexptr, fptr);
                        break;
                default:
                        printf("token %d, token_value %d\n", t, t_value);
        }

	putc('\n', fptr); // write character to file
	fclose(fptr);     // close file
}
