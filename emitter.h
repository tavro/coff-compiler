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
